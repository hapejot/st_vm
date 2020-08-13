#include <stdio.h>
#include "obj.h"
#include "values.h"
#include <string.h>

CONTINUATION sym_compare( CLOSURE clr ) {
    VALUE self = clr->tmp[0];
    VALUE cnt = clr->tmp[1];
    CONTINUATION cont = value_continuation(cnt);
    VALUE x = clr->tmp[2];
    switch ( VALUE_KIND( self ) ) {
        case KIND_STR:
            if( VALUE_KIND( x ) ) {
                int result = strcmp( value_symbol_str( self ),
                                         value_symbol_str( x ) );
                VALUE res;
                VALUE_LONG(res) = 0;
                VALUE_KIND(res) = KIND_INT;
                VALUE_IDX(res) = result;
                printf( "==: %d %04lx idx:%d\n",result,  VALUE_LONG(res), VALUE_IDX(cont->tref) );
                cont->closure->tmp[VALUE_IDX(cont->tref)] = res;
                value_closure_dump(cont->closure);
            }
            else {
                printf( "unexpected KIND: %04lx", VALUE_LONG( x ) );
            }
            break;
    }
    return cont;
}
