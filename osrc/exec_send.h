#ifndef _EXEC_SEND_H
#define _EXEC_SEND_H
VALUE t = *code++;
VALUE sel = *code++;
VALUE cls = value_obj_class( param[0] );
CLS_MTH *m = _lookup_method_and_class( cls, sel );
printf( " <%s>", value_symbol_str( sel ) );
if( m ) {
    printf( "\nEXEC:%d\n", m->no );
    CLOSURE c = value_closure_mk(  );
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
    printf( " method not found for obj %04lx class %04lx.", VALUE_LONG(param[0]), VALUE_LONG(cls) );
    return;
}

value_closure_dump( clr );
#endif
