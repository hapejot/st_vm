#include <stdio.h>
#include "obj.h"
#include "values.h"
#include <string.h>

API CONTINUATION obj_identical( CLOSURE clr ) {
    printf(" IDENTITY ");
    VALUE self = clr->tmp[0];
    VALUE cnt = clr->tmp[1];
    CONTINUATION cont = value_continuation( cnt );
    VALUE x = clr->tmp[2];
    VALUE res;
    if( VALUE_LONG( x ) == VALUE_LONG( self ) ) {
        res = true_val;
    }
    else{
        res = false_val;
    }
    cont->closure->tmp[VALUE_IDX( cont->tref )] = res;
    value_closure_dump( cont->closure );
    return cont;
}
