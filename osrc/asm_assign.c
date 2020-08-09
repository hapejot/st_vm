#include "obj.h"
#include "values.h"

static OPCODE *_opcode( VALUE name ) {
    for( uint_t i = 1; i < MAX_OPCODES; i++ ) {
        OPCODE *o = opcodes + i;
        if( o->defined && value_eq( o->name, name ) ) {
            o->code = i;
            return o;
        }
    }
    return NULL;
}

void asm_assign( CLS_MTH * method, VALUE * argv ) {
    uint_t pos0;                // local position of target value
    uint_t pos1;
    uint_t argc = 1;
    uint_t arg_offset = 2;
    printf( "ASSIGN" );
/* opcode could be the assign itself or the first name after 
 * the symbol.
 * first we check for an opcode at position 2.
 * if that wasnt successful, we assume that it is a simple
 * value assign
 */

    OPCODE *opcode = _opcode( argv[2] );
    if( opcode ) {
        argc = opcode->args;
        arg_offset = 3;
    }
    else {
        opcode = _opcode( sym.assign );
        argc = 1;
    }
    printf( " OP %d %s", opcode->code, value_symbol_str( opcode->name ) );
    value_code_emit_o( opcode->code );

/* 
 * target value has to be a local, compare to l-value 
 * the target value could be a temp variable or an instance 
 * variable
 */

    int ivar_pos = value_ivar_pos( method->cls, argv[0] );
    printf( " IVAR: %d", ivar_pos );
    if( ivar_pos < 0 ) {
        char l = locals_lookup( &pos0, method->vars, argv[0] );
        if( l == ' ' ) {
            locals_add( &method->vars, argv[0], 'T' );
            locals_lookup( &pos0, method->vars, argv[0] );
        }
        printf( " %c(%d)", l, pos0 );
        value_code_emit_v( value_mk( KIND_TREF, pos0 ) );
    }
    else
        value_code_emit_v( value_mk( KIND_IREF, ivar_pos ) );


    for( uint_t i = 0; i < argc; i++ ) {
        VALUE v = argv[arg_offset + i];
        char l = locals_lookup( &pos1, method->vars, v );
        if( l != ' ' ) {
            printf( " %c %d", l, pos1 );
            value_code_emit_v( value_mk( KIND_TREF, pos1 ) );
        }
        else {
            value_code_emit_v( v );
        }
    }
}
