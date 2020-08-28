#include "values.h"
#include <stdio.h>

void values_print(VALUE x){
    switch ( VALUE_KIND( x ) ) {
        case KIND_INT:
            printf( "INT<%d>", VALUE_IDX(x) );
            break;
        case KIND_STR:
            printf( "STR<%s>", value_symbol_str(x) );
            break;
        case KIND_OPC:
            printf( "OPC<%d>", VALUE_IDX(x) );
            break;
        case KIND_REF:
            printf( "REF<%d>", VALUE_IDX(x) );
            break;
        case KIND_TREF:
            printf("TREF<%d>", VALUE_IDX(x));
            break;
        case KIND_OBJ:
            printf("OBJ<%04x> CLS:", VALUE_IDX(x));
            values_print(value_obj_class(x));
            break;
        case KIND_CONT:
            printf("CONT<%d>", VALUE_IDX(x));
            CONTINUATION cnt = value_continuation(x);
            printf(" %p ", (void*)cnt->closure);
            values_print(cnt->ref);
            values_print(cnt->tref);
            break;
        case KIND_BLK:
            printf("BLOCK<%d> ", VALUE_IDX(x));
            BLOCK b = value_block_ptr(x);
            values_print(b->ref);
            // printf(" CLR:%p", (void*)b->clr);
            printf(" tmps:%d", b->temps);
            break;
        default:
            printf( "<%d>%05x", VALUE_KIND( x ), VALUE_IDX(x) );
            break;
    }
}
