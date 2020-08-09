#define EXTERN_DLL extern __declspec(dllimport)
#define DLL __declspec(dllimport)

#include "obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <dlfcn.h>

#include "key_val.h"
#include "cls_mth.h"

#define MAXMETH 100
#define MAXGLOBALS 100
CLS_MTH methods[MAXMETH];
KEY_VAL globals[MAXGLOBALS];
uint_t top_methods = 0;
CLS_MTH *method;                // current method

#define OP_END 0
#define OP_PARAM 1
#define OP_SEND 2
#define OP_TMPVAR 3
#define OP_GLOBAL 4
#define OP_CONTINUE 5

#define MAX_OPCODES 100
OPCODE opcodes[MAX_OPCODES];

#include "closure.h"
#define MAX_CLOSURES 100
struct closure closures[MAX_CLOSURES];

void *prim_lib;
/*
 * CONTINUATION
 *
 *
 *
 */
typedef struct continuation * CONTINUATION;
struct continuation {
    bool active;
    VALUE ref; // code reference to continue
    VALUE tref; // temporary variable position to store results
    CLOSURE closure;
};
static struct continuation continuations[100];

/*
 * PROTOTYPES
 */


/*
 * IMPLEMENTATION
 *
 *
 *
 *
 */
void print_line( WORDS ws ) {
    char *sep = "-:";
    while( ws ) {
        printf( "%s<%s>", sep, ws->str );
        ws = ws->next;
        sep = " ";
    }
    printf( "\n" );
    fflush( stdout );
}

#include "method_dump.h"

VALUE value_parse( char *str ) {
    VALUE r;
    if( str[0] == '#' )
        r = value_int( atoi( str + 1 ) );
    return r;
}

bool _initialized = false;
struct sym  sym;

#include "init_symbols.h"

uint_t _op_find( VALUE name ) {
    for( uint i = 0; i < 100; i++ ) {
        if( opcodes[i].defined && value_eq( opcodes[i].name, name ) ) {
            return i;
        }
    }
    return 0;
}

/* RUNTIME 
 *
 * should be pushed to a sparate module but has dependencies to the
 * method defintions, which are also needed by the code generator.
 *
 */



static CLS_MTH *_lookup_method_and_class( VALUE cls, VALUE sel ) {
    CLS_MTH *result = NULL;
    for( uint_t i = 0; i < top_methods; i++ ) {
        if( methods[i].cls.u.l == cls.u.l && methods[i].sel.u.l == sel.u.l ) {
            result = methods + i;
            break;
        }
    }
    return result;
}


static CLOSURE _closure_mk(  ) {
    for(uint_t i = 0;i<MAX_CLOSURES;i++){
        CLOSURE clr = closures+i;
        if(!clr->active){
            clr->active = true;
            return clr;
        }
    }
    return NULL;
}


static void _closure_dump( CLOSURE clr ) {
    printf( "\nCLOSURE: %p", ( void * )clr );
    for( uint_t i = 0; i < 10; i++ ) {
        printf( "\n  %d. %04lx", i, clr->tmp[i].u.l );
    }
}


static VALUE _continuation_new( CLOSURE clr, VALUE ref, VALUE tref ) {
    VALUE r = {.u.l = 0 };
    for( uint_t i = 0; i < 100; i++ ) {
        CONTINUATION cc = continuations + i;
        if( !cc->active ) {
            cc->active = true;
            cc->closure = clr;
            cc->ref = ref;
            cc->tref = tref;

            r.u.v.idx = i;
            r.u.v.kind = KIND_CONT;
            break;
        }
    }
    return r;
}

static CONTINUATION _continuation( VALUE c ){
    if( c.u.v.kind == KIND_CONT ){
        return continuations + c.u.v.idx;
    }
    else
        return NULL;
}

#include "exec.h"

int main( int argc, char **argv ) {

    char timestr[200];
    time_t t;
    struct tm *tmp;

    t = time( NULL );
    tmp = localtime( &t );
    strftime( timestr, sizeof( timestr ), "%Y-%m-%d %H:%M:%S", tmp );
    printf( "ST VM %s\n", timestr );

    if( argc != 4 ) {
        printf( "usage: %s <file> <class> <method>\n", argv[0] );
        exit( -1 );
    }
    FILE *in = fopen( argv[1], "r" );
    LINES lines = o_read_lines( in );
    for( LINES l = lines; l; l = l->next ) {
        VALUE line[20];
        int idx = 0;
        for( WORDS w = l->words; w; w = w->next ) {
            line[idx++] = value_symbol( w->str );
        }
        for( ; idx < 20; idx++ )
            value_clear( &line[idx] );
        _asm_line( idx, line );
    }
    CLS_MTH *m = _lookup_method_and_class( _global( value_symbol( argv[2] ) ),
                                           value_symbol( argv[3] ) );
    if( m ) {
        value_obj_dump(  );
        method_dump(  );
        value_ivar_dump();
        printf( "M:%d\n", m->no );
        _exec( _closure_mk(  ), m->code );
    }
    return 0;
}
