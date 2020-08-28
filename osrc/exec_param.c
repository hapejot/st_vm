#include "obj.h"
#include "values.h"
#include <assert.h>

VALUE next_code_value( CONTEXT ctx ) {
    VALUE r = *ctx->code++;
    switch ( VALUE_KIND( r ) ) {
        case KIND_TREF:
            r = ctx->clr->tmp[VALUE_IDX( r )];
            break;
    }
    return r;
}


void exec_param( CONTEXT ctx ) {
    assert( ctx->tmp_msg != NULL );
    MESSAGE msg = ctx->tmp_msg;
    uint_t n = VALUE_IDX( msg->argc );
    msg->args[n] = next_code_value(ctx);
    VALUE_IDX( msg->argc ) = n + 1;
}
