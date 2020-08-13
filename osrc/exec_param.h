#ifndef _EXEC_PARAM_H
#define _EXEC_PARAM_H
VALUE v = *code++;
if( v.u.v.kind == KIND_TREF ) {
    param[params] = clr->tmp[VALUE_IDX( v )];
}
else {
    param[params] = v;
}

printf( " %d %04lx %d %p", params, VALUE_LONG( param[params] ),
        VALUE_KIND( v ), (void*)clr );
params++;
#endif
