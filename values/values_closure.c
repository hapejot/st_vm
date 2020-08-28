#include "obj.h"
#include "values.h"
#include "closure_int.h"

API CLOSURE value_closure_mk(  ) {
    for( uint_t i = 0; i < MAX_CLOSURES; i++ ) {
        CLOSURE clr = closures + i;
        if( !clr->active ) {
            clr->active = true;
            return clr;
        }
    }
    return NULL;
}


API void value_closure_dump( CLOSURE clr ) {
    printf( "\nCLOSURE: %p", ( void * )clr );
    uint max = sizeof( clr->tmp ) / sizeof( *clr->tmp ) - 1;
    while( max > 0 && VALUE_LONG( clr->tmp[max] ) == 0 )
        max--;
    for( uint_t i = 0; i <= max; i++ ) {
        printf( "\n  %d. ", i );
        values_print( clr->tmp[i] );
    }
}
