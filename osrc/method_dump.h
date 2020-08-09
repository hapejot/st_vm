#ifndef _METHOD_DUMP_H
#define _METHOD_DUMP_H
static void method_dump(  ) {
    printf( "\n\nMETHODS" );
    for( uint_t i = 0; i < top_methods; i++ ) {
        CLS_MTH *m = methods + i;
        printf( "\n%02d. %04lx %s", m->no, m->cls.u.l,
                value_symbol_str( m->sel ) );
    }
    printf( "\n------\n" );
}
#endif
