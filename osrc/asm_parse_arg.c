#include "obj.h"
#include "values.h"
#include <stdlib.h>
void asm_parse_arg( CLS_MTH * method, VALUE str ) {
    if( !value_isnil( str ) ) {
        uint pos;
        char l = locals_lookup( &pos, method->vars,
                                str );
        if( l != ' ' ) {
            value_code_emit_v( value_mk( KIND_TREF, pos ) );
        }
        else {
            const char *argstr = value_symbol_str( str );
            if( argstr[0] == '#' ) {
                int x = atoi( argstr + 1 );
                value_code_emit_v( value_mk( KIND_INT, x ) );
            }
            else
                value_code_emit_v( str );
        }
    }
}
