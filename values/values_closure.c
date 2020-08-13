#include "obj.h"
#include "values.h"
#include "closure_int.h"

API CLOSURE value_closure_mk(  ) {
    for(uint_t i = 0;i<MAX_CLOSURES;i++){
        CLOSURE clr = closures+i;
        if(!clr->active){
            clr->active = true;
            return clr;
        }
    }
    return NULL;
}


API void value_closure_dump( CLOSURE clr ) {
    printf( "\nCLOSURE: %p", ( void * )clr );
    for( uint_t i = 0; i < 10; i++ ) {
        printf( "\n  %d. %04lx", i, clr->tmp[i].u.l );
    }
}
