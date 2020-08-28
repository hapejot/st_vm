#include "obj.h"
#include "values.h"

#define MAX_BLOCKS 100
static struct block blocks[MAX_BLOCKS];

API VALUE value_block_new( CLOSURE clr, VALUE ref, VALUE temps ) {
    (void)clr;
    VALUE r;
    VALUE_LONG(r) = 0;
    for( uint_t i = 0; i < MAX_BLOCKS; i++ ) {
        BLOCK b = blocks + i;
        if( !b->active ) {
            b->active = true;
            b->ref = ref;
            // b->clr = clr;
            b->temps = VALUE_IDX(temps);

            VALUE_KIND(r) = KIND_BLK;
            VALUE_IDX(r) = i;
            break;
        }
    }
    return r;
}

API BLOCK value_block_ptr( VALUE b ){
    if( KIND_BLK == VALUE_KIND(b) ){
        return blocks + VALUE_IDX(b);
    }
    else
        return NULL;
}
