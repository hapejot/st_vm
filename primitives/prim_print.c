#include <stdio.h>
#include "obj.h"
#include "values.h"

API CONTINUATION print( CLOSURE clr ) {
    VALUE self = clr->tmp[0];
    CONTINUATION cont = value_continuation( clr->tmp[1] );
    switch ( VALUE_KIND( self ) ) {
        case KIND_STR:
            printf( "PRINT: %s\n", value_symbol_str( self ) );
            break;
        case KIND_INT:
            printf( "PRINT: %d\n", VALUE_IDX( self ) );
            break;
        default:
            printf( "PRINT: 0x%04lx\n", VALUE_LONG( self ) );
            break;
    }
    return cont;
}
