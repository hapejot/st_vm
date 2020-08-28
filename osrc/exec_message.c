#include "obj.h"
#include "values.h"
#include <assert.h>
#include <malloc.h>

void exec_message( CONTEXT ctx ) {
    MESSAGE msg = malloc( sizeof( *msg ) );
    msg->obj = next_code_value(ctx);
    msg->cont = next_code_value(ctx);
    VALUE_LONG(msg->argc) = 0;
    ctx->tmp_msg = msg;
}
