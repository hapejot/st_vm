#include "values.h"
#define MAXOBJ 1000
#include <stdio.h>
#include <assert.h>


static bool _initialized = false;

struct obj {
    bool active;
    VALUE cls;
    VALUE ivar[5];
};

struct obj objects[MAXOBJ];
VALUE sym_cls;
VALUE short_cls;
VALUE nil_cls;
VALUE bool_cls;
VALUE true_cls;
VALUE false_cls;
VALUE true_val;
VALUE false_val;
VALUE block_cls;
VALUE method_cls;

static void _initialize(  ) {
    _initialized = true;
    nil_cls = value_obj_new( nil_cls );
    sym_cls = value_obj_new( nil_cls );
    bool_cls = value_obj_new( nil_cls );
    true_cls = value_obj_new( nil_cls );
    false_cls = value_obj_new( nil_cls );
    true_val = value_obj_new( true_cls );
    false_val = value_obj_new( false_cls );
    block_cls = value_obj_new( nil_cls );
    short_cls = value_obj_new( nil_cls );
    method_cls = value_obj_new(nil_cls);
}

API void init_classes(  ) {
    _initialize(  );
}

API VALUE value_obj_new( VALUE cls ) {
    if( !_initialized )
        _initialize(  );
    VALUE o;
    VALUE_LONG(o) = 0;
    for( int i = 0; i < MAXOBJ; i++ ) {
        if( !objects[i].active ) {
            objects[i].active = true;
            objects[i].cls = cls;
            VALUE_KIND(o) = KIND_OBJ;
            VALUE_IDX(o) = i;
            break;
        }
    }
    return o;
}


API VALUE value_obj_class( VALUE o ) {
    assert( _initialized );
    VALUE r = {.u.l = 0 };
    switch ( VALUE_KIND( o ) ) {
        case KIND_OBJ:
            r = objects[VALUE_IDX( o )].cls;
            break;
        case KIND_STR:
            r = sym_cls;
            break;
        case KIND_BLK:
            r = block_cls;
            break;
        case KIND_METH:
            r = method_cls;
            break;
        case KIND_INT:
            r = short_cls;
            break;
    }
    return r;
}

API VALUE value_obj_ivar( VALUE o, VALUE ref ) {
    assert( _initialized );
    if( VALUE_KIND( o ) == KIND_OBJ && VALUE_KIND( ref ) == KIND_IREF ) {
        return objects[VALUE_IDX( o )].ivar[VALUE_IDX( ref )];
    }
    else {
        VALUE r = {.u.l = 0 };
        return r;
    }
}
API void value_obj_ivar_set( VALUE o, VALUE ref, VALUE v ) {
    assert( _initialized );
    if( VALUE_KIND( o ) == KIND_OBJ && VALUE_KIND( ref ) == KIND_IREF ) {
        objects[VALUE_IDX( o )].ivar[VALUE_IDX( ref )] = v;
    }
}

API void value_obj_dump(  ) {
    assert( _initialized );
    printf( "\n\nOBJECTS:" );
    for( int i = 0; i < MAXOBJ; i++ ) {
        if( objects[i].active ) {
            printf( "\n%03x5: %04lx", i, objects[i].cls.u.l );
        }
    }
    printf( "\n-----\n" );
}
