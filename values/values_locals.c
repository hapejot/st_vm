#include "values.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LOCALS 1000
static uint_t locals_top = 0;
struct locals locals[MAX_LOCALS];


VALUE value_locals_new(  ) {
    return value_mk(KIND_VAR, locals_top++);
}

LOCALS value_locals_ptr( VALUE l ) {
    assert( VALUE_KIND( l ) == KIND_VAR );
    return locals + VALUE_IDX( l );
}


void value_locals_dump(  ) {
    for( uint_t i = 0; i < locals_top; i++ ) {
        LOCALS l = locals + i;
        printf( "\n%04d %04lx %s %04lx", i, VALUE_LONG( l->owner ),
                value_symbol_str( l->name ), VALUE_LONG( l->def ) );
    }
}

struct locals find;
uint_t find_next;
struct locals_flags {
    bool owner;
} find_flags;

void value_locals_find( bool has_block, VALUE owner ) {
    find_flags.owner = has_block;
    find.owner = owner;
    find_next = 0;
}

LOCALS value_locals_next(  ) {
    LOCALS r = NULL;
    while( find_next < MAX_LOCALS ) {
        bool found = find_flags.owner
                && VALUE_LONG( find.owner ) ==
                VALUE_LONG( locals[find_next].owner );
        if( found ) {
            r = locals + find_next;
            break;
        }
        find_next++;
    }
    return r;
}
