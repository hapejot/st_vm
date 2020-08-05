#ifndef _VALUES_H
#define _VALUES_H
#include "platform.h"
#include <stdbool.h>
#include <sys/types.h>
typedef struct value
{
    union {
        struct
        {
            unsigned int kind : 4;
            unsigned int idx : 12;
        } v;
        ulong_t l;
    } u;
} VALUE;

#define KIND_INT 0
#define KIND_STR 1
#define KIND_OPC 2


VALUE value_dict_new(int size);
VALUE value_dict_at(VALUE dict, VALUE key);
VALUE value_dict_at_put(VALUE dict, VALUE key, VALUE val);

VALUE value_array_new(int size);
VALUE value_array_at(VALUE array, int idx);
VALUE value_array_at_set(VALUE array, int idx, VALUE el);

#undef API
#define API API_EXT
API bool value_eq(VALUE a, VALUE b);
API VALUE value_symbol( char *str );
#undef API
#define API API_DEF

#endif
