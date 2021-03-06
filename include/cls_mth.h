#ifndef _CLS_MTH_H
#define _CLS_MTH_H
typedef struct cls_mth {
    int no;
    VALUE cls;  // class id
    VALUE sel; // selector
    VALUE block;
    uint_t blockcnt;
    BLOCK current_block;
    LOCALVAR vars;
    uint_t codelen;
    VALUE code;
    uint_t tmpcnt;
} CLS_MTH;

extern CLS_MTH methods[];
extern uint_t top_methods;
#endif
