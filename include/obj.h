#ifndef _OBJ_H
#define _OBJ_H

typedef struct value {
    int kind:4;
    int idx:12;
} VALUE;

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

EXTERN_DLL WORDS o_read_words();
EXTERN_DLL LINES o_read_lines();

#endif