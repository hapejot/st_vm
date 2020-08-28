#include <stdio.h>
#include "obj.h"
#include "values.h"
#include <string.h>
#include <assert.h>

API bool obj_identical( MESSAGE msg ) {
    VALUE self = msg->obj;
    VALUE x = msg->args[0];
    VALUE res;
    if( VALUE_LONG( x ) == VALUE_LONG( self ) ) {
        res = true_val;
    }
    else{
        res = false_val;
    }
    if(msg->result) *msg->result = res;
    return true;
}
