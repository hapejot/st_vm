#include "obj.h"
#include <stdlib.h>

DLL LINES o_read_lines()
{
    LINES r = NULL;
    LINES *current = &r;
    for (;;)
    {
        WORDS words = o_read_words();
        if (words == eof)
            break;
        LINES l = calloc(1, sizeof(*l));
        l->words = words;
        (*current) = l;
        current = &l->next;
    }
    return r;
}