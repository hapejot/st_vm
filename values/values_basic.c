#include "values.h"


API bool value_eq(VALUE a, VALUE b){
    return a.u.l == b.u.l;
}

API void value_clear(VALUE *v){
    v->u.l = 0;
}

API bool value_isnil(VALUE v){
    return v.u.l == 0;
}

API VALUE value_nil(){
    VALUE v;
    value_clear(&v);
    return v;
}

API VALUE value_mk(uint_t kind, uint_t idx){
    VALUE v = { .u.l = 0 };
    v.u.v.kind = kind;
    v.u.v.idx = idx;
    return v;
}

API VALUE value_int( int i ) {
    VALUE r;
    r.u.v.idx = i;
    r.u.v.kind = KIND_INT;
    return r;
}
