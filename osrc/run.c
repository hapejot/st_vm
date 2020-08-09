
static CLS_MTH *_lookup_method_and_class( VALUE cls, VALUE sel ) {
    CLS_MTH *result = NULL;
    for( uint_t i = 0; i < top_methods; i++ ) {
        if( methods[i].cls.u.l == cls.u.l && methods[i].sel.u.l == sel.u.l ) {
            result = methods + i;
            break;
        }
    }
    return result;
}
