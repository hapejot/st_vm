#define EXTERN_DLL  extern __declspec(dllimport)
#define DLL  __declspec(dllimport)

#include "obj.h"
#include <stdio.h>

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

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    LINES lines = o_read_lines();
    for (LINES l = lines; l; l = l->next)
    {
        print_line(l->words);
    }
    return 0;
}