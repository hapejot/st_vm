#ifndef _EXEC_SEND_H
#define _EXEC_SEND_H
VALUE t = *code++;
VALUE sel = *code++;
CLS_MTH *m = _lookup_method_and_class( value_obj_class( param[0] ), sel );
printf( " <%s>", value_symbol_str( sel ) );
if( m ) {
    printf( "\nEXEC:%d\n", m->no );
    CLOSURE c = _closure_mk(  );
    for( uint_t i = 0; i < params; i++ ) {
        c->tmp[i] = param[i];
    }
    params = 0;
// _exec( c, m->code );
    clr = c;
    ref = m->code;
    printf( "\nNEW REF: %04lx", ref.u.l );
    code = value_code_ptr( ref );
    ( void )t;
}
else {
    printf( " method nod found." );
    return;
}

_closure_dump( clr );
#endif
