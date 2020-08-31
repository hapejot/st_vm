#include "values.h"


API bool value_eq(VALUE a, VALUE b){
    return VALUE_LONG(a) == VALUE_LONG(b);
}

API void value_clear(VALUE *v){
    VALUE_LONG(*v) = 0;
}

API bool value_isnil(VALUE v){
    return VALUE_LONG(v) == 0;
}

API VALUE value_nil(){
    VALUE v;
    value_clear(&v);
    return v;
}

API VALUE value_mk(uint_t kind, uint_t idx){
    VALUE v;
    VALUE_LONG(v) = 0;
    VALUE_KIND(v) = kind;
    VALUE_IDX(v) = idx;
    return v;
}

API VALUE value_int( int i ) {
    return value_mk(KIND_INT, i);
}
