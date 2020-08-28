#include "obj.h"
#include "values.h"

void exec_cont(CONTEXT ctx){
#define code (ctx->code)
#define clr (ctx->clr)
VALUE t = *code++;
// assert(VALUE_KIND(t) == KIND_TREF);
uint_t tidx = VALUE_IDX( t );
VALUE l = *code++;
VALUE r = *code++;
// assert(VALUE_KIND(l) == KIND_REF);
// assert(VALUE_KIND(r) == KIND_TREF);
clr->tmp[tidx] = value_continuation_new( clr, l, r );
/*
printf( "\n%p new continuation %d <- (%04lx %04lx %04lx)", (void*)code, tidx,
        VALUE_LONG( clr->tmp[tidx] ), VALUE_LONG( l ), VALUE_LONG( r ) );
*/
}
