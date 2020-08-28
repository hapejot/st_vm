#include "obj.h"
#include "values.h"
#include <assert.h>

void exec_send( CONTEXT ctx ) {
    VALUE t = *( ctx->code )++;
    VALUE sel = next_code_value( ctx );
    assert( VALUE_KIND( t ) == KIND_TREF );
    VALUE *tref = ctx->clr->tmp + VALUE_IDX( t );

    ctx->exec_msg = ctx->tmp_msg;
    ctx->exec_msg->result = tref;
    ctx->tmp_msg = NULL;
    VALUE cls = value_obj_class( ctx->exec_msg->obj );
    CLS_MTH *m = lookup_method_and_class( cls, sel );
    if( m ) {
        ctx->clr = value_closure_mk(  );
        ctx->clr->tmp[0] = ctx->exec_msg->obj;
        ctx->clr->tmp[1] = ctx->exec_msg->cont;
        uint_t n = VALUE_IDX( ctx->exec_msg->argc );
        for( uint_t i = 0; i < n; i++ ) {
            ctx->clr->tmp[2 + i] = ctx->exec_msg->args[i];
        }
        ctx->ref = m->code;
        ctx->code = value_code_ptr( ctx->ref );
    }
    else {
        printf( " method not found for obj %04lx class %04lx.",
                VALUE_LONG( ctx->exec_msg->obj ), VALUE_LONG( cls ) );
        return;
    }
    ( void )t;
}
