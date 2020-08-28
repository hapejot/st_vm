#ifndef _INIT_SYMBOLS_H
#define _INIT_SYMBOLS_H

void _disass_default( VALUE * lcode ) {
    static VALUE *base = NULL;
    if( !base ) {
        VALUE tmp;
        VALUE_KIND( tmp ) = KIND_REF;
        VALUE_IDX( tmp ) = 0;
        base = value_code_ptr( tmp );
        printf( "\nbase:%p", ( void * )base );
    }
    VALUE o = lcode[0];
    if( o.u.v.kind == KIND_OPC ) {
        uint_t n = o.u.v.idx;
        OPCODE *op = opcodes + n;
        printf( "\n%ld -- %s", lcode - base, value_symbol_str( op->name ) );
        uint start = 1;
        if( op->assign ) {
            putchar( ' ' );
            values_print( lcode[start++] );
            printf( " <-" );
        }
        for( uint i = 0; i < op->args; i++ ) {
            putchar( ' ' );
            values_print( lcode[start + i] );
        }
    }
}
void _register_op( OPCODE * op, char *name, VALUE * sym, uint_t args, OPEXEC exe ) {
    *sym = value_symbol( name );
    op->name = *sym;
    op->defined = true;
    op->args = args;
    op->dis = _disass_default;
    op->exe = exe;
}

void _init_symbols(  ) {
    if( !_initialized ) {
        sym.method = value_symbol( "method" );
        sym.tmpvar = value_symbol( "tmpvar" );
        sym.global = value_symbol( "global" );
        sym.param = value_symbol( "param" );
        sym.send = value_symbol( "send" );
        sym._continue = value_symbol( "continue" );
        sym.jump = value_symbol( "jump" );
        sym.instvar = value_symbol( "instvar" );
        sym.mkcont = value_symbol( "mkcont" );
        sym.assign = value_symbol( "<-" );
        sym.end = value_symbol( "end" );
        sym.label = value_symbol( ":" );
        sym.cls = value_symbol( "class" );
        sym.new = value_symbol( "new" );
        sym.go_to = value_symbol( "goto" );
        sym.primitive = value_symbol( "primitive" );
        sym.block = value_symbol( "block" );
        sym.call = value_symbol( "call" );
        sym.self = value_symbol("self");
        _initialized = true;


        struct opcode *op = opcodes + 1;
        op->name = sym.param;
        op->defined = true;
        op->args = 1;
        op->dis = _disass_default;

        op++;
        op->name = sym.send;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym._continue;
        op->assign = true;                       // means, the code uses assign syntax
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym.jump;
        op->defined = true;
        op->args = 1;
        op->dis = _disass_default;

        op++;
        op->name = sym.assign;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym.global;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym.new;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym.go_to;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym.primitive;
        op->defined = true;
        op->args = 1;
        op->dis = _disass_default;

        op++;
        op->name = sym.block;
        op->assign = true;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        op++;
        op->name = sym.call;
        op->defined = true;
        op->args = 2;
        op->dis = _disass_default;

        _register_op( ++op, "message", &sym.message, 2, exec_message );
        _register_op( ++op, "closure", &sym.closure, 0, NULL );
        _register_op( ++op, "parvar", &sym.parvar, 1, NULL );
    }
}
#endif
