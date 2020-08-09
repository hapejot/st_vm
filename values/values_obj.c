#include "values.h"
#define MAXOBJ 1000
#include <stdio.h>

struct obj {
    bool    active;
    VALUE cls;
    VALUE ivar[5];
};

struct obj objects[MAXOBJ];


API VALUE value_obj_new(VALUE cls){
    VALUE o;
    for(int i=0;i< MAXOBJ;i++){
        if(!objects[i].active) {
           objects[i].active = true;
          objects[i].cls = cls; 
          o.u.v.kind = KIND_OBJ;
          o.u.v.idx = i;
          break;
        }
    }
    return o;
}


API VALUE value_obj_class(VALUE o){
    VALUE r = { .u.l = 0 };
    if(o.u.v.kind == KIND_OBJ){
        r = objects[o.u.v.idx].cls;
    }
    return r;
}

API VALUE value_obj_ivar(VALUE o, VALUE ref){
    if(VALUE_KIND(o) == KIND_OBJ && VALUE_KIND(ref) == KIND_IREF){
        return objects[VALUE_IDX(o)].ivar[VALUE_IDX(ref)];
    }
    else
    {
        VALUE r = {.u.l = 0};
        return r;
    }
}
API void value_obj_ivar_set(VALUE o, VALUE ref, VALUE v){
    if(VALUE_KIND(o) == KIND_OBJ && VALUE_KIND(ref) == KIND_IREF){
        objects[VALUE_IDX(o)].ivar[VALUE_IDX(ref)] = v;
    }
}

API void value_obj_dump(){
    printf("\n\nOBJECTS:");
    for(int i=0;i< MAXOBJ;i++){
        if(objects[i].active){
            printf("\n%03x5: %04lx", i, objects[i].cls.u.l);
        }
    }
    printf("\n-----\n");
}
