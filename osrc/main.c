#define EXTERN_DLL extern __declspec(dllimport)
#define DLL __declspec(dllimport)

#include "obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void _asm_line(WORDS ws)
{
    if (ws)
    {
        if (strcmp("method", ws->str) == 0)
        {
            WORDS w1 = ws->next;
            WORDS w2 = w1->next;
            WORDS w3 = w2->next;
            printf("METHOD %30s for %s\n", w1->str, w3->str);
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
        // print_line(l->words);
        _asm_line(l->words);
    }
    return 0;
}