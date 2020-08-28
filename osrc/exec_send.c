#include "obj.h"
#include "values.h"

void exec_send( CONTEXT ctx ) {
    ctx->exec_msg = ctx->tmp_msg;
    ctx->tmp_msg = NULL;
    VALUE t = *( ctx->code )++;
    VALUE sel = *( ctx->code )++;
    VALUE cls = value_obj_class( ctx->exec_msg->obj );
    CLS_MTH *m = lookup_method_and_class( cls, sel );
    if( m ) {
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
