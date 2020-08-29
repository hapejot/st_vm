#include "obj.h"
#include "values.h"
#include <assert.h>

void continuation_follow( CONTEXT ctx, CONTINUATION cc, VALUE tv ) {
    if( cc ) {
        uint_t idx_t = VALUE_IDX( cc->tref );
        values_print( tv );
        printf( " to T%d", idx_t );
        cc->closure->tmp[idx_t] = tv;
        ctx->clr = cc->closure;
        printf( "\nNEW REF: %04lx", cc->ref.u.l );
        ctx->code = value_code_ptr( cc->ref );
    }
    else
        ctx->code = NULL;
}

void exec_goto( CONTEXT ctx ) {
    VALUE t = *( ctx->code )++; // ref to temp of continuation
    if( VALUE_KIND( t ) == KIND_TREF )
        t = ctx->clr->tmp[VALUE_IDX( t )];
    assert(VALUE_KIND(t) == KIND_REF );
    CONTINUATION cc = value_continuation( t );
    continuation_follow( ctx, cc, ctx->exec_msg->result );
}
