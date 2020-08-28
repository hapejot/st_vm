#include "obj.h"
#include "values.h"
#include <assert.h>
void exec_call( CONTEXT ctx ) {
#define code (ctx->code)
#define closure (ctx->clr)
    VALUE t = *code++;
    VALUE continuation = *code++;
    if( VALUE_KIND( t ) == KIND_TREF ) {
        t = closure->tmp[VALUE_IDX( t )];
    }
    if( VALUE_KIND( t ) != KIND_BLK ) {
        printf( "Arg is no block" );
    }
    BLOCK b = value_block_ptr( t );
    assert( VALUE_KIND( continuation ) == KIND_TREF );
    VALUE cont = closure->tmp[VALUE_IDX( continuation )];
    //    closure = b->clr;
    closure->tmp[1] = cont;
    code = value_code_ptr( b->ref );
}
