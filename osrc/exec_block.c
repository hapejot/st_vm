#include "obj.h"
#include "values.h"
void exec_block( CONTEXT ctx ) {
    ( void )ctx;
    VALUE t = *ctx->code++;
    switch ( VALUE_KIND( t ) ) {
        case KIND_TREF:
            ctx->clr->tmp[VALUE_IDX( t )] = value_code_start_block(  );
            break;
        default:
            printf( "\nillegal value kind for target: %d", VALUE_KIND( t ) );
            break;
    }
}
