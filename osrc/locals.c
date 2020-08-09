#include "obj.h"
#include "values.h"
#include <malloc.h>

struct localvar {
    VALUE name;
    char type;                  // P - Parameter, T - Temporary, G - Global Reference
    LOCALVAR next;
};



void locals_clear( LOCALVAR * vars ) {
    *vars = NULL;
}

void locals_add( LOCALVAR *vars, VALUE name, char type)
{
    LOCALVAR *v = vars;
    while(*v) {
        v = &((*v)->next);
    }
    LOCALVAR new = malloc(sizeof(*new));
    *v = new;
    new->name = name;
    new->type = type;
    new->next = NULL;
}


void locals_dump(LOCALVAR vars){
    uint_t n = 0;
    while(vars){
        printf("\n%02d - %-20s %c", n, value_symbol_str(vars->name), vars->type);
        vars = vars->next;
        n++;
    }
}

char locals_lookup(uint_t *pos, LOCALVAR vars, VALUE name){
    char type = ' ';
    uint_t lpos = 0;
    while(vars){
        if(value_eq(name, vars->name)){
            *pos = lpos;
            return vars->type;
        }
        lpos++;
        vars = vars->next;
    }
    return type;
}
