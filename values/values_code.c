#include "values.h"
#include <stdio.h>

OPCODE opcodes[MAX_OPCODES];

#define MAXCODE 1000

VALUE code[MAXCODE];
uint_t top;
uint_t start;

API void value_code_dump( VALUE ptr, uint_t count ) {
    for( uint_t i = 0; i < count; i++ ) {
        uint_t idx = ptr.u.v.idx + i;
        VALUE o = code[idx];
        switch ( o.u.v.kind ) {
            case KIND_INT:
                printf( " %d", o.u.v.idx );
                break;
            case KIND_STR:
                printf( " %s", value_symbol_str( o ) );
                break;
            case KIND_OPC:
                printf( "\n-- %04x : %s", idx,
                        value_symbol_str( opcodes[o.u.v.idx].name ) );
                break;
            case KIND_REF:
                printf( " 0x%04x", o.u.v.idx );
                break;
            case KIND_TREF:
                printf( " T%d", o.u.v.idx );
                break;
        }
    }
}

API void value_code_emit_o( int op ) {
    VALUE *v = code + top;
    v->u.v.kind = KIND_OPC;
    v->u.v.idx = op;
    top++;
}

API void value_code_emit_v( VALUE src ) {
    VALUE *v = code + top;
    v->u.l = src.u.l;
    top++;
}

API VALUE value_code_emit_fixup( VALUE v ) {
    printf("\nFIXING %s  [%x-%x]", value_symbol_str(v), start, top);
    for( uint_t i = start; i < top; i++ ) {
        if( value_eq( v, code[i] ) ) {
            printf("\n- at %04x", i);
            code[i] = value_mk( KIND_REF, top );
        }
    }
    return value_mk(KIND_REF, top);
}

API VALUE value_code_start(  ) {
    start = top;
    return value_mk( KIND_REF, top );
}

API uint_t value_code_len(  ) {
    return top - start;
}

API VALUE *value_code_ptr( VALUE ref ) {
    if( ref.u.v.kind == KIND_REF )
        return code + ref.u.v.idx;
    else
        return NULL;
}
