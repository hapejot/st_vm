#ifndef _OBJ_H
#define _OBJ_H
#include "platform.h"
#include <stdio.h>

#include "values.h"

typedef struct object
{
    VALUE cls;
    VALUE data;
} OBJECT;
#define MAXMEM 10000
#define MAXOBJ 1000
VALUE memory[MAXMEM];
OBJECT objects[MAXOBJ];

typedef struct word *WORDS;
typedef struct line *LINES;

struct word
{
    char *str;
    WORDS next;
};
struct line
{
    WORDS words;
    LINES next;
};
extern WORDS eof;

typedef struct localvar *LOCALVAR;



extern struct sym {
    VALUE method;
    VALUE tmpvar;
    VALUE global;
    VALUE param;
    VALUE send;
    VALUE cont;
    VALUE jump;
    VALUE instvar;
    VALUE mkcont;
    VALUE assign;
    VALUE end;
    VALUE label;
    VALUE cls;
    VALUE new;
    VALUE go_to;
    VALUE primitive;
    VALUE block;
    VALUE call;
    VALUE message;
    VALUE closure;
} sym;
#include "cls_mth.h"
#include "closure.h"
#include "osrc.func.h"

#endif
