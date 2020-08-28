#include "obj.h"
#include "values.h"

void exec_global( CONTEXT ctx ) {
#define code (ctx->code)
#define clr (ctx->clr)
    VALUE t = *code++;
    VALUE g = _global( *code++ );
    uint_t tidx = t.u.v.idx;
    printf( "\nhandling global var %d <- %lx", tidx, g.u.l );
    clr->tmp[tidx] = g;
}
