#ifndef _CLOSURE_H
#define _CLOSURE_H
/*
 * CLOSURE
 *
 *
 *
 */

struct closure {
    bool active;
    VALUE tmp[20];
};

extern struct closure closures[];
#endif
