#include "obj.h"
#include "values.h"
#include <assert.h>
void exec_call( CONTEXT ctx ) {
/*
 * call <target> <continuation>
 *
 * <target> is expected to be a block that should be executed
 *  after completion of the block -> the last goto should use 
 * <continuation> is the point where processing should continue after
 *      the block's processing has been finished.
 */

    VALUE t = *ctx->code++;
    VALUE continuation = *ctx->code++;

    if( VALUE_KIND( t ) == KIND_TREF ) {
        t = ctx->clr->tmp[VALUE_IDX( t )];
    }
    if( VALUE_KIND( t ) != KIND_BLK ) {
        printf( "Arg is no block" );
    }
    BLOCK b = value_block_ptr( t );
    assert( VALUE_KIND( continuation ) == KIND_TREF );
    VALUE cont = ctx->clr->tmp[VALUE_IDX( continuation )];
    //    closure = b->clr;
    ctx->clr->tmp[1] = cont;
    ctx->code = value_code_ptr( b->ref );
}
