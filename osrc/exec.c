#include "obj.h"
#include "values.h"
#include <string.h>

static void _wait_input( CONTEXT ctx ) {
    char line[100];
    VALUE o = ctx->code[0];
    if( VALUE_KIND( o ) == KIND_OPC ) {
        uint_t n = VALUE_IDX( o );
        while( true ) {
            DISASS dis = opcodes[n].dis;
            if( dis )
                ( *dis ) ( ctx->code );
            printf( "\n>>>>>" );
            memset( line, 0, sizeof( line ) );
            fgets( line, sizeof( line ), stdin );
            for( uint i = 0; i < sizeof( line ); i++ ) {
                if( line[i] == '\n' )
                    line[i] = '\0';
            }
            if( strlen( line ) == 0 )
                return;
            else if( line[0] == 'c' )            // print closure
            {
                value_closure_dump( ctx->clr );
            }
            else if( line[0] == 'm' ) {
                dump_message( ctx->tmp_msg );
            }
        }
    }
    else {
        printf( "\n%p KIND: %d - Error", ( void * )ctx->code,
                VALUE_KIND( o ) );
    }
}

void exec( CONTEXT ctx ) {
    ctx->code = value_code_ptr( ctx->ref );
    while( ctx->code ) {
        _wait_input( ctx );
        VALUE o = *( ctx->code )++;
        if( VALUE_KIND( o ) != KIND_OPC )
            break;
        uint_t n = VALUE_IDX( o );
        VALUE name = opcodes[n].name;
        if( VALUE_IDX( o ) ) {
            if( opcodes[n].exe ) {
                ( *opcodes[n].exe ) ( ctx );
            }
            else if( value_eq( sym.param, name ) ) {
                exec_param( ctx );
            }
            else if( value_eq( sym.global, name ) ) {
                exec_global( ctx );
            }
            else if( value_eq( sym.cont, name ) ) {
                exec_cont( ctx );
            }
            else if( value_eq( sym.send, name ) ) {
                exec_send( ctx );
            }
            else if( value_eq( sym.new, name ) ) {
                exec_new( ctx );
            }
            else if( value_eq( sym.go_to, name ) ) {
                exec_goto( ctx );
            }
            else if( value_eq( sym.assign, name ) ) {
                exec_assign( ctx );
            }
            else if( value_eq( sym.primitive, name ) ) {
                exec_primitive( ctx );
            }
            else if( value_eq( sym.block, name ) ) {
                exec_block( ctx );
            }
            else if( value_eq( sym.call, name ) ) {
                exec_call( ctx );
            }
        }
    }
}
