#include "obj.h"
#include "values.h"

void continuation_follow( CONTEXT ctx, CONTINUATION cc, VALUE tv ) {
        // printf( " continuation %04lx -> %p", t.u.l, ( void * )cc );
        uint_t idx_s = VALUE_IDX(tv);
        uint_t idx_t = VALUE_IDX(cc->tref);
        printf( " from T%d to T%d", idx_s, idx_t );
        cc->closure->tmp[idx_t] = ctx->clr->tmp[idx_s];
        ctx->clr = cc->closure;
        printf( "\nNEW REF: %04lx", cc->ref.u.l );
        ctx->code = value_code_ptr( cc->ref );
}

void exec_goto(CONTEXT ctx) {
    VALUE t = *(ctx->code)++;          // ref to temp of continuation
    VALUE tv = *(ctx->code)++;         // ref to target value 
    if( VALUE_KIND( t ) == KIND_TREF ) {
        t = ctx->clr->tmp[VALUE_IDX( t )];
    }
    CONTINUATION cc = value_continuation( t );
    if( cc ) 
        continuation_follow(ctx, cc, tv);
    else {
        printf( "\nNO CONTINUATION" );
        return;
    }
}
