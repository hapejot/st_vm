#include "obj.h"
#include "values.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
extern CLS_MTH*method;

/*
 * adds the block the the current method
 */
API void method_add_block(VALUE block){
    method->block = block;
    method->current_block = value_block_ptr(block);
}
