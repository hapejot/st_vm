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

API void o_add_word(WORDS *words, const char *);
API WORDS o_read_words(FILE *);
API LINES o_read_lines(FILE *);
API VALUE intern_string(char *str);

#endif