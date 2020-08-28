#ifndef _EXEC_H
#define _EXEC_H




static void _wait_input( CLOSURE clr, VALUE ref, VALUE * code, uint params, VALUE*param ) {
    ( void )clr;
    ( void )ref;
    ( void )code;
    char line[100];
    VALUE o = code[0];
    if( VALUE_KIND( o ) == KIND_OPC ) {
        uint_t n = VALUE_IDX( o );
        while( true ) {
            DISASS dis = opcodes[n].dis;
            if( dis )
                ( *dis ) ( code );
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
                value_closure_dump( clr );
            }
            else if( line[0] == 'p' ) // print params
            {
                for(uint i=0;i< params;i++){
                    printf("\n%d. ", i);
                    values_print(param[i]);
                }
            }
        }
    }
    else {
        printf( "\n%p KIND: %d - Error", ( void * )code, VALUE_KIND( o ) );
    }
}

static void _exec( CLOSURE clr, VALUE ref ) {
    VALUE param[10];
    uint_t params = 0;
    VALUE *code = value_code_ptr( ref );
    value_closure_dump( clr );
    while( code ) {
        _wait_input( clr, ref, code, params, param );
        VALUE o = *code++;
        if( o.u.v.kind != KIND_OPC )
            break;
        uint_t n = o.u.v.idx;
        VALUE name = opcodes[n].name;
        switch ( o.u.v.kind ) {
            case KIND_INT:
                printf( " %d", o.u.v.idx );
                break;
            case KIND_STR:
                printf( " %s", value_symbol_str( o ) );
                break;
            case KIND_OPC:
                if( o.u.v.idx ) {
                    if( value_eq( sym.param, name ) ) {
                    }
                    else if( value_eq( sym.global, name ) ) {
                    }
                    else if( value_eq( sym.cont, name ) ) {
                    }
                    else if( value_eq( sym.send, name ) ) {
                    }
                    else if( value_eq( sym.new, name ) ) {
                    }
                    else if( value_eq( sym.go_to, name ) ) {
                        exec_goto( &clr, &code );
                    }
                    else if( value_eq( sym.assign, name ) ) {
                        exec_assign( clr, &code );
                    }
                    else if( value_eq( sym.primitive, name ) ) {
                        exec_primitive( clr, params, param, &code );
                        params = 0;
                    }
                    else if( value_eq( sym.block, name ) ) {
                        exec_block( clr, &code );
                    }
                    else if( value_eq( sym.call, name ) ) {
exec_call(&clr, &code);
                    }
                }
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
#endif
