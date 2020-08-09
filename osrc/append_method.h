#ifndef _APPEND_METHOD_H
#define _APPEND_METHOD_H
#include "cls_mth.h"
CLS_MTH *_append_method( VALUE cls, VALUE sel ) {
    CLS_MTH *m = methods + top_methods;
    m->cls.u.l = cls.u.l;
    m->sel.u.l = sel.u.l;
    top_methods++;
    m->no = top_methods;
    m->codelen = 0;
    return m;
}
#endif
