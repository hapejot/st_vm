/* values_print.c */
API void values_print(VALUE x);
/* values_symbol.c */
API VALUE value_symbol(char *str);
API const char *value_symbol_str(VALUE v);
/* values_code.c */
API void value_code_dump(VALUE ptr, uint_t count);
API void value_code_emit_o(int op);
API void value_code_emit_v(VALUE src);
API void value_code_emit_fixup(VALUE v);
API VALUE value_code_start(void);
API uint_t value_code_len(void);
API VALUE *value_code_ptr(VALUE ref);
/* values_obj.c */
API void init_classes(void);
API VALUE value_obj_new(VALUE cls);
API VALUE value_obj_class(VALUE o);
API VALUE value_obj_ivar(VALUE o, VALUE ref);
API void value_obj_ivar_set(VALUE o, VALUE ref, VALUE v);
API void value_obj_dump(void);
/* values_closure.c */
API CLOSURE value_closure_mk(void);
API void value_closure_dump(CLOSURE clr);
/* values_block.c */
API VALUE value_block_new(CLOSURE clr, VALUE ref, VALUE temps);
API BLOCK value_block_ptr(VALUE b);
/* values_basic.c */
API _Bool value_eq(VALUE a, VALUE b);
API void value_clear(VALUE *v);
API _Bool value_isnil(VALUE v);
API VALUE value_nil(void);
API VALUE value_mk(uint_t kind, uint_t idx);
API VALUE value_int(int i);
/* values_continuation.c */
API VALUE value_continuation_new(CLOSURE clr, VALUE ref, VALUE tref);
API CONTINUATION value_continuation(VALUE c);
/* values_ivars.c */
API void value_ivar_append(VALUE clsname, VALUE varname);
API VALUE value_ivar_at(VALUE clsname, uint_t pos);
API int value_ivar_pos(VALUE clsname, VALUE varname);
API void value_ivar_dump(void);
