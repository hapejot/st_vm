#include "obj.h"
#include "values.h"

VALUE asm_classname(VALUE cls_name){
    VALUE cls = _global( cls_name );
    if( value_isnil( cls ) ) {
        VALUE meta = value_obj_new( value_nil(  ) );
        cls = value_obj_new( meta );
        _global_put( cls_name, cls );
    }
    return cls;
}

void asm_method( CLS_MTH ** methp, VALUE * argv ) {
#define method (*methp)
    VALUE cls = asm_classname(argv[3]);
    if( value_eq( sym.cls, argv[4] ) ) {
        method = _append_method( value_obj_class( cls ), argv[1] );
    }
    else
        method = _append_method( cls, argv[1] );
    printf( "METHOD  %d %s", method->no, value_symbol_str( argv[1] ) );
    method->code = value_code_start(  );
}
