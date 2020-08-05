#include "values.h"
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define STRMAX 10000
static char _str[STRMAX];
static size_t _top = 0;


API VALUE value_symbol( char *str ) {
    uint_t n = strlen( str ) + 1;  // include zero terminator
    VALUE result = {.u.v.kind = 15};
    for( uint_t i = 0; _top > n && i <= _top - n; i++ ) {
        if( memcmp( _str + i, str, n ) == 0 ) {
            result.u.v.kind = KIND_STR;
            result.u.v.idx = i;
            break;
        }
    }
    if(result.u.v.kind != KIND_STR ) {
        strcpy( _str + _top, str );
        result.u.v.kind = KIND_STR;
        result.u.v.idx = _top;
        _top += n;
        assert( _top < STRMAX );
    }
    return result;
}
