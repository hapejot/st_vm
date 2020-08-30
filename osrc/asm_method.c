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
    CLS_MTH *m = NULL;
    if( value_eq( sym.cls, argv[4] ) ) {
        m = _append_method( value_obj_class( cls ), argv[1] );
    }
    else
        m = _append_method( cls, argv[1] );
    m->block = value_code_start_block();
    m->blockcnt = 1;
    m->current_block = value_block_ptr(m->block);
    m->code = value_code_start(  );
    *methp = m;
}
