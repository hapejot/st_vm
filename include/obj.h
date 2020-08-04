#ifndef _OBJ_H
#define _OBJ_H
#include <stdio.h>

typedef struct value {
    int kind:4;
    int idx:12;
} VALUE;

#define KIND_INT    0
#define KING_STR    1

typedef struct object {
    VALUE cls;
    VALUE data;
} OBJECT;
#define MAXMEM 10000
#define MAXOBJ 1000
VALUE memory[MAXMEM];
OBJECT objects[MAXOBJ];

typedef struct word *WORDS;
typedef struct line *LINES;

struct word {
    char*   str;
    WORDS    next;
};
struct line {
    WORDS    words;
    LINES    next;
};
extern WORDS eof;

#ifndef DLL
#define EXTERN_DLL  extern __declspec(dllexport)
#define DLL  __declspec(dllexport)
#endif
EXTERN_DLL void o_add_word(WORDS *words, const char*);
EXTERN_DLL WORDS o_read_words(FILE*);
EXTERN_DLL LINES o_read_lines(FILE*);

#endif