#define EXTERN_DLL extern __declspec(dllimport)
#define DLL __declspec(dllimport)

#include "obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct cls_mth
{
    int no;
    VALUE cls;
    VALUE sel;
    WORDS vars;
    WORDS globals;
    int codelen;
    VALUE code[100];
} CLS_MTH;
#define MAXMETH 100
CLS_MTH methods[MAXMETH];
size_t top_methods = 0;
CLS_MTH *method; // current method

#define OP_END 0
#define OP_PARAM 1
#define OP_SEND 2
#define OP_TMPVAR 3
#define OP_GLOBAL 4
#define OP_CONTINUE 5

VALUE value_int(int i)
{
    VALUE r;
    r.u.v.idx = i;
    r.u.v.kind = KIND_INT;
    return r;
}

void print_line(WORDS ws)
{
    char *sep = "-:";
    while (ws)
    {
        printf("%s<%s>", sep, ws->str);
        ws = ws->next;
        sep = " ";
    }
    printf("\n");
    fflush(stdout);
}

void global_add(char *name)
{
    o_add_word(&method->globals, name);
}

int global_idx(char *name)
{
    WORDS w = method->globals;
    int i = 0;
    while (w)
    {
        if (strcmp(w->str, name) == 0)
            return i;
        i++;
        w = w->next;
    }
    return -1;
}

void local_add(char *name)
{
    o_add_word(&method->vars, name);
}

int local_idx(char *name)
{
    WORDS w = method->vars;
    int i = 0;
    while (w)
    {
        if (strcmp(w->str, name) == 0)
            return i;
        i++;
        w = w->next;
    }
    return -1;
}

CLS_MTH *_lookup_method_and_class(VALUE cls, VALUE sel)
{
    bool found = false;
    CLS_MTH *result = NULL;
    for (int i = 0; i < top_methods; i++)
    {
        if (methods[i].cls.u.l == cls.u.l && methods[i].sel.u.l == sel.u.l)
        {
            found = true;
            result = methods + i;
            break;
        }
    }
    return result;
}
CLS_MTH *_append_method(VALUE cls, VALUE sel)
{
    CLS_MTH *m = methods + top_methods;
    m->cls.u.l = cls.u.l;
    m->sel.u.l = sel.u.l;
    top_methods++;
    m->no = top_methods;
    m->codelen = 0;
    return m;
}

bool _argv_from_words(int *argc, char ***argv, WORDS ws)
{
    bool result = false;
    static char *_args[30];
    *argc = 0;
    while (ws)
    {
        _args[*argc] = ws->str;
        ws = ws->next;
        (*argc)++;
        result = true;
        *argv = &_args;
    }
    return result;
}

void emit_o(int op)
{
    VALUE *v = method->code + method->codelen;
    v->u.v.kind = KIND_OPC;
    v->u.v.idx = op;
    method->codelen++;
}

void emit_v(VALUE src)
{
    VALUE *v = method->code + method->codelen;
    v->u.l = src.u.l;
    method->codelen++;
}

VALUE value_parse(char *str)
{
    VALUE r;
    if (str[0] == '#')
        r = value_int(atoi(str + 1));
    return r;
}

bool _initialized = false;
struct {
    VALUE method;
}   sym;
void _init()
{
    if (!_initialized)
    {
        sym.method = value_symbol("method");
        _initialized = true;
    }
}


void _asm_line(int argc, VALUE *argv)
{
    _init();
    if (strcmp("method", argv[0]) == 0)
    {
        WORDS w1 = ws->next;
        WORDS w2 = w1->next;
        WORDS w3 = w2->next;
        VALUE sel = intern_string(w1->str);
        VALUE cls = intern_string(w3->str);
        CLS_MTH *m = _lookup_method_and_class(cls, sel);
        if (NULL == m)
        {
            m = _append_method(cls, sel);
        }
        printf("METHOD %30s for %-20s  %d\n", w1->str, w3->str, m->no);
    }
    else if (strcmp("param", argv[0]) == 0)
    {
        emit_o(OP_PARAM);
    }
}
}
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (argc != 2)
        exit(-1);
    FILE *in = fopen(argv[1], "r");
    LINES lines = o_read_lines(in);
    for (LINES l = lines; l; l = l->next)
    {
        VALUE line[20];
        int idx = 0;
        for (WORDS w = l->words; w; w = w->next)
        {
            line[idx++] = value_symbol(w->str);
        }
        _asm_line(idx, line);
    }
    return 0;
}