#include "values.h"
#include <assert.h>
#include <stdio.h>

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
