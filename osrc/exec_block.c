#include "obj.h"
#include "values.h"
void exec_block(CONTEXT ctx) {
#define code (ctx->code)
    VALUE t = *code++;
    VALUE s = *code++;
    VALUE n = *code++;
    ctx->clr->tmp[VALUE_IDX( t )] = value_block_new( s, n );
}
