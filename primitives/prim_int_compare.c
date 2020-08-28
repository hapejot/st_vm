#include <stdio.h>
#include "obj.h"
#include "values.h"
#include <string.h>

bool int_compare( MESSAGE msg ) {
    VALUE self = msg->obj;
    VALUE x = msg->args[0];
    switch ( VALUE_KIND( self ) ) {
        case KIND_INT:
            if( VALUE_KIND( x ) == KIND_INT ) {
                int result = VALUE_IDX( self ) - VALUE_IDX( x );

                VALUE res;
                VALUE_LONG( res ) = 0;
                VALUE_KIND( res ) = KIND_INT;
                VALUE_IDX( res ) = result < 0 ? -1 : ( result == 0 ? 0 : 1 );
                (void)res;
            }
            else {
                printf( "unexpected KIND: %04lx", VALUE_LONG( x ) );
            }
            break;
    }
    return true;
}
