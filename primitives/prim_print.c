#include <stdio.h>
#include "obj.h"
#include "values.h"

API bool print( MESSAGE msg ) {
    VALUE self = msg->obj;
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
    return true;
}
