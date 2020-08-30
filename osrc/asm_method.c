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
    VALUE cls = asm_classname(argv[3]);
    if( value_eq( sym.cls, argv[4] ) ) {
        *methp = _append_method( value_obj_class( cls ), argv[1] );
    }
    else
        *methp = _append_method( cls, argv[1] );
    (*methp)->block[0] = value_code_start_block();
    (*methp)->blockcnt = 1;
    (*methp)->code = value_code_start(  );
}
