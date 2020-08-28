/* o_read_words.c */
API void o_add_word(WORDS *words, const char *w);
API WORDS _read_word(FILE *in, int idx);
API WORDS o_read_words(FILE *in);
/* o_read_lines.c */
API LINES o_read_lines(FILE *in);
/* oint.c */
API void o_loop(void);
/* locals.c */
API void locals_clear(LOCALVAR *vars);
API void locals_add(LOCALVAR *vars, VALUE name, char type);
API void locals_dump(LOCALVAR vars);
API char locals_lookup(uint_t *pos, LOCALVAR vars, VALUE name);
/* asm.c */
API void _globals_initialize(void);
API void init_globals(void);
API void _global_put(VALUE key, VALUE value);
API VALUE _global(VALUE key);
API void _globals_dump(void);
API CLS_MTH *_append_method(VALUE cls, VALUE sel);
API void _asm_line(int argc, VALUE *argv);
/* methods.c */
/* asm_parse_arg.c */
API void asm_parse_arg(CLS_MTH *method, VALUE str);
/* asm_assign.c */
API void asm_assign(CLS_MTH *method, VALUE *argv);
/* asm_method.c */
API VALUE asm_classname(VALUE cls_name);
API void asm_method(CLS_MTH **methp, VALUE *argv);
/* exec_assign.c */
API void exec_assign(CONTEXT ctx);
/* exec_primitive.c */
API void exec_primitive(CONTEXT ctx);
/* exec_global.c */
API void exec_global(CONTEXT ctx);
/* exec_block.c */
API void exec_block(CONTEXT ctx);
/* exec_param.c */
API VALUE next_code_value(CONTEXT ctx);
API void exec_param(CONTEXT ctx);
/* exec_cont.c */
API void exec_cont(CONTEXT ctx);
/* exec_new.c */
API void exec_new(CONTEXT ctx);
/* exec_message.c */
API void exec_message(CONTEXT ctx);
/* exec.c */
API void exec(CONTEXT ctx);
/* exec_call.c */
API void exec_call(CONTEXT ctx);
/* exec_send.c */
API void exec_send(CONTEXT ctx);
/* exec_goto.c */
API void continuation_follow(CONTEXT ctx, CONTINUATION cc, VALUE tv);
API void exec_goto(CONTEXT ctx);
/* dump_message.c */
API void dump_message(MESSAGE msg);
/* main.c */
API void print_line(WORDS ws);
API VALUE value_parse(char *str);
API void _disass_default(VALUE *lcode);
API void _register_op(OPCODE *op, char *name, VALUE *sym, uint_t args, OPEXEC exe);
API void _init_symbols(void);
API uint_t _op_find(VALUE name);
API CLS_MTH *lookup_method_and_class(VALUE cls, VALUE sel);
API int main(int argc, char **argv);
