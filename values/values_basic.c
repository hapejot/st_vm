#include "values.h"


API bool value_eq(VALUE a, VALUE b){
    return a.u.l == b.u.l;
}