#include "obj.h"
#include "values.h"
#include <stdio.h>

void exec_new(CONTEXT ctx) {
#define code (ctx->code)
    VALUE t = *code++;
    VALUE cname = *code++;
    VALUE ivars = *code++;
    ( void )ivars;                               // will be used later
    VALUE cls = _global( cname );
    if( value_isnil( cls ) ) {
        printf( " class not found" );
        return;
    }
    VALUE o = value_obj_new( cls );
    ctx->clr->tmp[t.u.v.idx] = o;
    printf( " 0x%04lx <- 0x%04lx", t.u.l, o.u.l );
}
