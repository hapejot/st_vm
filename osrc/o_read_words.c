#include "obj.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

struct word newline = {.str = "\n", .next = NULL };
struct word eof_struct  = {.str = "#EOF#", .next = NULL };
WORDS eof = &eof_struct;

DLL void o_add_word(WORDS*words, const char* w){
  WORDS new;
  while(*words){
    words = &(*words)->next;
  }
  new = calloc(1, sizeof(*new));
  new->str = strdup(w);
  new->next = NULL;
  *words = new;
}


DLL WORDS _read_word(FILE *in, int idx)
{
  WORDS w = NULL;
  int c = fgetc(in);
  if (c > 0 && !isspace(c))
  {
    w = _read_word(in, idx + 1);
    w->str[idx] = (char)c;
  }
  else
  {
    if (idx > 0)
    {
      w = calloc(1, sizeof(*w));
      w->str = calloc(1, idx + 1);
      ungetc(c, in);
    }
    else if (c == 10)
    {
      return &newline;
    }
  }
  return w;
}

/* 
 * reads a single line from terminal and parses it into an array of tokens/words by 
 * splitting the line on spaces.  Adds NULL as final token 
 */
WORDS o_read_words(FILE *in)
{
  WORDS r = eof;
  WORDS *current = &r;
  while (!feof(in))
  {
    if(r == eof) r = NULL;
    WORDS w = _read_word(in, 0);
    if (w == &newline)
      break;
    if (w)
    {
      *current = w;
      current = &w->next;
    }
  }
  return r;
}