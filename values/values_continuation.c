#include "obj.h"
#include "values.h"
#include "continuation_int.h"

API VALUE value_continuation_new( CLOSURE clr, VALUE ref, VALUE tref ) {
    VALUE r = {.u.l = 0 };
    for( uint_t i = 0; i < 100; i++ ) {
        CONTINUATION cc = continuations + i;
        if( !cc->active ) {
            cc->active = true;
            cc->closure = clr;
            cc->ref = ref;
            cc->tref = tref;

            VALUE_IDX(r) = i;
            VALUE_KIND(r) = KIND_CONT;
            break;
        }
    }
    return r;
}

API CONTINUATION value_continuation( VALUE c ){
    if( VALUE_KIND(c) == KIND_CONT ){
        return continuations + c.u.v.idx;
    }
    else
        return NULL;
}
