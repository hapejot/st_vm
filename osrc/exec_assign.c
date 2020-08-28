#include "obj.h"
#include "values.h"

void exec_assign(CONTEXT ctx) {
#define code (ctx->code)
#define clr (ctx->clr)
    VALUE t = *code++;
    VALUE s = *code++;
    switch ( VALUE_KIND( s ) ) {
        case KIND_TREF:
            s = clr->tmp[VALUE_IDX( s )];
            break;
        case KIND_IREF:
            s = value_obj_ivar( clr->tmp[0], s );
            printf( "S:IREF %lx", VALUE_LONG( s ) );
            break;
    }
    switch ( VALUE_KIND( t ) ) {
        case KIND_TREF:
            clr->tmp[VALUE_IDX( t )] = s;
            break;
        case KIND_IREF:
            value_obj_ivar_set( clr->tmp[0], t, s );
            printf( "IVAR %d <- %lx", VALUE_IDX( t ), VALUE_LONG( s ) );
            break;
        default:
            printf( "\nILLEGAL TARGET TYPE" );
            return;
            break;
    }
}
