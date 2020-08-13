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
            int idx : 12;
        } v;
        ulong_t l;
    } u;
} VALUE;

typedef struct opcode {
    VALUE name;
    int params;
    bool assign;
    bool defined;
    uint_t args;
    uint_t code;
} OPCODE;

extern VALUE sym_cls;
extern VALUE true_cls;
extern VALUE false_cls;
extern VALUE bool_cls;
extern VALUE true_val;
extern VALUE false_val;
extern VALUE block_cls;

#define MAX_OPCODES 100
extern OPCODE opcodes[];

#define KIND_INT 0 // Small Integer
#define KIND_STR 1 // String or Symbol
#define KIND_OPC 2 // Opcode
#define KIND_REF 3 // Code Reference
#define KIND_TREF 4 // reference for temporary variable
#define KIND_OBJ 5 // regular object
#define KIND_MEM 6 // memory reference
#define KIND_CPR 7 // code pointer
#define KIND_CONT 8 // continuation
#define KIND_IREF 9

#define VALUE_KIND(x) ((x).u.v.kind)
#define VALUE_IDX(x)  ((x).u.v.idx)
#define VALUE_LONG(x) ((x).u.l)

#include "closure.h"
#include "continuation.h"

#undef API
#define API API_EXT
#include "values.func.h"
#undef API
#define API API_DEF

#endif
