#include "obj.h"
#include "values.h"
#include <assert.h>

// VALUE next_code_value( CONTEXT ctx ) {


void exec_return( CONTEXT ctx ) {
    MESSAGE msg = ctx->exec_msg;
    assert( msg != NULL );
    msg->result = next_code_value(ctx);
}
