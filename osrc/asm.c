#include "obj.h"
#include "values.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct key_val {
    VALUE key;
    VALUE value;
} KEY_VAL;
#define MAXGLOBALS 10
KEY_VAL globals[MAXGLOBALS];

#include "cls_mth.h"
CLS_MTH *method;

static bool _global_idx( uint_t * idx, VALUE key ) {
    bool found = false;
    for( uint_t i = 0; i < MAXGLOBALS; i++ ) {
        if( value_eq( globals[i].key, key ) ) {
            found = true;
            *idx = i;
            break;
        }
        else if( globals[i].key.u.l == 0 ) {
            *idx = i;
            break;
        }
    }
    return found;
}

void _global_put( VALUE key, VALUE value ) {
    uint_t idx;
    if( _global_idx( &idx, key ) ) {
        globals[idx].value = value;
    }
    else {
        globals[idx].key = key;
        globals[idx].value = value;
    }
}

VALUE _global( VALUE key ) {
    VALUE r = {.u.l = 0 };
    for( uint_t i = 0; i < MAXGLOBALS; i++ ) {
        if( value_eq( globals[i].key, key ) ) {
            r = globals[i].value;
            break;
        }
    }
    return r;
}

#include "append_method.h"
void _asm_line( int argc, VALUE * argv ) {
    static uint_t lineno = 1;
    _init_symbols(  );
    printf( "%03d:", lineno );
    if( value_eq( sym.method, argv[0] ) && argc >= 4 ) {
        asm_method( &method, argv );
    }
    else if( value_eq( sym.tmpvar, argv[0] ) ) {
        printf( "TMP %s", value_symbol_str( argv[1] ) );
        locals_add( &method->vars, argv[1], 'T' );
    }
    else if( value_eq( sym.global, argv[0] ) ) {
        uint_t pos;
        printf( "GLOBAL %s", value_symbol_str( argv[1] ) );
        locals_add( &method->vars, argv[1], 'G' );
        value_code_emit_o( _op_find( sym.global ) );
        locals_lookup( &pos, method->vars, argv[1] );
        value_code_emit_v( value_mk( KIND_TREF, pos ) );
        value_code_emit_v( argv[1] );
    }
    else if( value_eq( sym.end, argv[0] ) ) {
        printf( "END" );
        locals_dump( method->vars );
        method->codelen = value_code_len(  );
        value_code_dump( method->code, method->codelen );

    }
    else if(value_eq(sym.instvar, argv[0])){
        printf("INSTVAR");
        value_ivar_append(asm_classname(argv[3]), argv[1]);
    }
    else if( value_eq( sym.label, argv[1] ) ) {
        printf( "LABEL" );
        value_code_emit_fixup( argv[0] );
    }
    else if( value_eq( sym.assign, argv[1] ) ) {
        asm_assign( method, argv );
    }
    else {
        for( uint_t i = 0; i < MAX_OPCODES; i++ ) {
            if( opcodes[i].defined ) {
                if( value_eq( opcodes[i].name, argv[0] ) ) {
                    printf( "OP %d %s", i, value_symbol_str( argv[0] ) );
                    value_code_emit_o( i );
                    uint_t pos;
                    for( uint j = 1; j < 4; j++ ) {
                        if( !value_isnil( argv[j] ) ) {
                            char l = locals_lookup( &pos, method->vars,
                                                    argv[j] );
                            if( l != ' ' ) {
                                value_code_emit_v( value_mk
                                                   ( KIND_TREF, pos ) );
                            }
                            else
                                value_code_emit_v( argv[j] );
                        }
                    }
                    break;
                }
            }
        }
    }
    lineno++;
    printf( "\n" );
}