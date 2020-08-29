#include "obj.h"
#include "values.h"
#include <dlfcn.h>
#include <assert.h>

static void *prim_lib;

void exec_primitive( CONTEXT ctx ) {
    if( prim_lib == NULL ) {
        prim_lib = dlopen( "bin/libprimitives.so", RTLD_LAZY );
    }
    if( prim_lib ) {
        bool ( *prim ) ( MESSAGE );
        VALUE t = *ctx->code++;
        assert( VALUE_KIND( t ) == KIND_TREF );

        VALUE s = *ctx->code++;
        const char *name = value_symbol_str( s );
        *( void ** )&prim = dlsym( prim_lib, name );
        if( prim ) {
            MESSAGE msg = ctx->tmp_msg;
            if( prim( msg ) ) {
                CONTINUATION cc = value_continuation( msg->cont );
                continuation_follow( ctx, cc, msg->result );
            }
            else {
                printf( "\nPRIM: %s: failed", name );
            }
        }
    }
    ctx->tmp_msg = NULL;
}
