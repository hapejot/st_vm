#include "values.h"
#include <stdio.h>

typedef struct ivar *IVAR;

struct ivar {
    bool active;
    VALUE clsname;
    VALUE varname;
    uint_t pos;
};

#define MAX_IVARS 100

struct ivar ivars[MAX_IVARS];


API void value_ivar_append( VALUE clsname, VALUE varname ) {
    uint_t pos = 0;
    IVAR candidate = NULL;
    for( uint_t i = 0; i < MAX_IVARS; i++ ) {
        IVAR x = ivars + i;
        if( x->active ) {
            if( value_eq( x->clsname, clsname ) ) {
                if( pos <= x->pos )
                    pos = x->pos + 1;
                if( value_eq( x->varname, varname ) ) {
                    break;
                }
            }
        }
        else {
            candidate = x;
        }
    }
    candidate->active = true;
    candidate->clsname = clsname;
    candidate->varname = varname;
    candidate->pos = pos;
}

API VALUE value_ivar_at( VALUE clsname, uint_t pos ) {
    VALUE r = {.u.l = 0 };
    for( uint_t i = 0; i < MAX_IVARS; i++ ) {
        IVAR x = ivars + i;
        if( x->active && value_eq( x->clsname, clsname )
            && x->pos == pos ) {
            r = x->varname;
            break;
        }
    }
    return r;
}

API int value_ivar_pos( VALUE clsname, VALUE varname ) {
    int r = -1;
    for( uint_t i = 0; i < MAX_IVARS; i++ ) {
        IVAR x = ivars + i;
        if( x->active && value_eq( x->clsname, clsname )
            && value_eq( x->varname, varname ) ) {
            r = x->pos;
            break;
        }
    }
    return r;
}

API void value_ivar_dump(  ) {
    printf( "\nINSTANCE VARIABLES" );
    for( uint_t i = 0; i < MAX_IVARS; i++ ) {
        IVAR x = ivars + i;
        if( x->active )
            printf( "\n%lx %d. %s", x->clsname.u.l,
                    x->pos, value_symbol_str( x->varname ) );
    }
    printf( "\n" );
}
