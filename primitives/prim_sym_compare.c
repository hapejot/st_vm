#include <stdio.h>
#include "obj.h"
#include "values.h"
#include <string.h>

API bool sym_compare( MESSAGE msg ) {
    VALUE self = msg->obj;
    VALUE x = msg->args[0];
    switch ( VALUE_KIND( self ) ) {
        case KIND_STR:
            if( VALUE_KIND( x ) ) {
                int result = strcmp( value_symbol_str( self ),
                                     value_symbol_str( x ) );
                VALUE res;
                VALUE_LONG( res ) = 0;
                VALUE_KIND( res ) = KIND_INT;
                VALUE_IDX( res ) = result;
                ( void )res;
                if(msg->result) *msg->result = res;
            }
            else {
                printf( "unexpected KIND: %04lx", VALUE_LONG( x ) );
            }
            break;
        default:
            printf("\ncan only compare symbols");
    }
    return true;
}
