#ifndef _APPEND_METHOD_H
#define _APPEND_METHOD_H
#include "cls_mth.h"
CLS_MTH *_append_method( VALUE cls, VALUE sel ) {
    CLS_MTH *m = methods + top_methods;
    VALUE_LONG(m->cls) = VALUE_LONG(cls);
    VALUE_LONG(m->sel) = VALUE_LONG(sel);
    top_methods++;
    m->no = top_methods;
    m->codelen = 0;
    return m;
}
#endif
