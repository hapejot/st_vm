#ifndef _INIT_SYMBOLS_H
#define _INIT_SYMBOLS_H
void _init_symbols(  ) {
    if( !_initialized ) {
        sym.method = value_symbol( "method" );
        sym.tmpvar = value_symbol( "tmpvar" );
        sym.global = value_symbol( "global" );
        sym.param = value_symbol( "param" );
        sym.send = value_symbol( "send" );
        sym.cont = value_symbol( "continue" );
        sym.jump = value_symbol( "jump" );
        sym.instvar = value_symbol( "instvar" );
        sym.mkcont = value_symbol( "mkcont" );
        sym.assign = value_symbol( "<-" );
        sym.end = value_symbol( "end" );
        sym.label = value_symbol( ":" );
        sym.cls = value_symbol( "class" );
        sym.new = value_symbol( "new" );
        sym.go_to = value_symbol("goto");
        sym.primitive = value_symbol("primitive");
        _initialized = true;


        struct opcode *op = opcodes + 1;
        op->name = sym.param;
        op->defined = true;
        op->args = 1;
        op++;
        op->name = sym.send;
        op->defined = true;
        op->args = 1;
        op++;
        op->name = sym.cont;
        op->assign = true;                       // means, the code uses assign syntax
        op->defined = true;
        op->args = 2;
        op++;
        op->name = sym.jump;
        op->defined = true;
        op->args = 1;
        op++;
        op->name = sym.assign;
        op->defined = true;
        op->args = 0;
        op++;
        op->name = sym.global;
        op->defined = true;
        op->args = 1;

        op++;
        op->name = sym.new;
        op->defined = true;
        op->args = 2;
        op++;
        op->name = sym.go_to;
        op->defined = true;
        op->args = 1;

        op++;
        op->name = sym.primitive;
        op->defined = true;
        op->args = 1;
    }
}
#endif
