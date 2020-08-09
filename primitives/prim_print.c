#include <stdio.h>
#include "obj.h"
#include "values.h"

void print( CLOSURE clr ) {
    VALUE self = clr->tmp[0];
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
}
