#include "values.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LOCALS 1000
uint_t top = 0;
struct locals locals[MAX_LOCALS];


VALUE value_locals_new(  ) {
    VALUE r;
    assert( top < MAX_LOCALS );
    VALUE_KIND( r ) = KIND_VAR;
    VALUE_IDX( r ) = top++;
    return r;
}

LOCALS value_locals_ptr( VALUE l ) {
    assert( VALUE_KIND( l ) == KIND_VAR );
    return locals + VALUE_IDX( l );
}


void value_locals_dump(  ) {
    for( uint_t i = 0; i < top; i++ ) {
        LOCALS l = locals + i;
        printf( "\n%04d %04lx %s %04lx", i, VALUE_LONG( l->block ),
                value_symbol_str( l->name ), VALUE_LONG( l->def ) );
    }
}

struct locals find;
uint_t find_next;
struct locals_flags {
    bool block;
} find_flags;

void value_locals_find( bool has_block, VALUE block ) {
    find_flags.block = has_block;
    find.block = block;
    find_next = 0;
}

LOCALS value_locals_next(  ) {
    LOCALS r = NULL;
    while( find_next < MAX_LOCALS ) {
        bool found = find_flags.block
                && VALUE_LONG( find.block ) ==
                VALUE_LONG( locals[find_next].block );
        if( found ) {
            r = locals + find_next;
            break;
        }
        find_next++;
    }
    return r;
}
