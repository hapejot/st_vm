#include "obj.h"
#include <malloc.h>
#include <string.h>

#define STRMAX 10000
static char _str[STRMAX];
static size_t _top = 0;


VALUE intern_string( char *str ) {
    int n = strlen( str ) + 1;  // include zero terminator
    VALUE result = {.kind = 15};
    for( int i = 0; i <= _top - n; i++ ) {
        if( memcmp( _str + i, str, n ) == 0 ) {
            result.kind = KIND_STR;
            result.idx = i;
            break;
        }
    }
    if(result.kind != KIND_STR ) {
        strcpy( _str + _top, str );
        result.kind = KIND_STR;
        result.idx = _top;
        _top += n;
        assert( _top < STRMAX );
    }
    return result;
}