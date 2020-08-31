#include "obj.h"
#include "values.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct key_val {
    VALUE key;
    VALUE value;
} KEY_VAL;
#define MAXGLOBALS 10
KEY_VAL globals[MAXGLOBALS];

#include "cls_mth.h"
CLS_MTH *method;

BLOCK current_block_ptr;
VALUE current_block;

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

static bool globals_initialized = false;
void _globals_initialize(  ) {
    globals_initialized = true;
    _global_put( value_symbol( "Symbol" ), sym_cls );
    _global_put( value_symbol( "Boolean" ), bool_cls );
    _global_put( value_symbol( "True" ), true_cls );
    _global_put( value_symbol( "False" ), false_cls );
    _global_put( value_symbol( "Block" ), block_cls );
    _global_put( value_symbol( "SmallInteger" ), short_cls );


    printf( "\nsym cls: %04lx", VALUE_LONG( sym_cls ) );
}

void init_globals(  ) {
    _globals_initialize(  );
}

void _global_put( VALUE key, VALUE value ) {
    uint_t idx;
    if( !globals_initialized )
        _globals_initialize(  );
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
    if( !globals_initialized )
        _globals_initialize(  );

    for( uint_t i = 0; i < MAXGLOBALS; i++ ) {
        if( value_eq( globals[i].key, key ) ) {
            r = globals[i].value;
            break;
        }
    }
    return r;
}

void _globals_dump(  ) {
    printf( "\nGLOBALS" );
    for( uint_t i = 0; i < MAXGLOBALS; i++ ) {
        if( VALUE_KIND( globals[i].key ) == KIND_STR ) {
            printf( "\n%s: %04lx", value_symbol_str( globals[i].key ),
                    VALUE_LONG( globals[i].value ) );
        }
    }
    printf( "\n---\n" );
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

        LOCALS l = value_locals_ptr(value_locals_new());
        l->block = method->block;
        l->name = argv[1];
        l->def = value_mk(KIND_TREF, method->tmpcnt++);
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
        BLOCK b = method->current_block;
        assert( b );
        b->length = value_code_len(  );
        value_code_dump( b->ref, b->length );

    }
    else if( value_eq( sym.instvar, argv[0] ) ) {
        printf( "INSTVAR" );
        value_ivar_append( asm_classname( argv[3] ), argv[1] );
    }
    else if( value_eq( sym.label, argv[1] ) ) {
        printf( "LABEL" );
        value_code_emit_fixup( argv[0] );
    }
    else if( value_eq( sym.block, argv[1] ) ) {
        method_add_block( value_code_start_block(  ) );
    }
    else if( value_eq( sym.assign, argv[1] ) ) {
        asm_assign( method, argv );
    }
    else {
        for( uint_t i = 0; i < MAX_OPCODES; i++ ) {
            if( opcodes[i].defined ) {
                if( value_eq( opcodes[i].name, argv[0] ) ) {
                    OPCODE *op = opcodes + i;
                    printf( "OP %d %s", i, value_symbol_str( argv[0] ) );
                    value_code_emit_o( i );
                    for( uint j = 0; j < op->args; j++ ) {
                        asm_parse_arg( method, argv[1 + j] );
                    }
                    break;
                }
            }
        }
    }
    lineno++;
    printf( "\n" );
}
