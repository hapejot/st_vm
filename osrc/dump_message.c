#include "values.h"
#include <stdio.h>

void dump_message( MESSAGE msg ) {
    printf( "\nMessage" );
    if( msg ) {
        printf( "\nSelf: " );
        values_print( msg->obj );
        printf( "\nCont: " );
        values_print( msg->cont );
        uint_t n = VALUE_IDX( msg->argc );
        for( uint_t i = 0; i < n; i++ ) {
            printf( "\n%d. ", i + 1 );
            values_print( msg->args[i] );
        }
    }
    else {
        printf( " not defined" );
    }
}
