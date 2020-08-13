#ifndef _EXEC_CONT_H
#define _EXEC_CONT_H
VALUE t = *code++;
uint_t tidx = VALUE_IDX(t);
VALUE l = *code++;
VALUE r = *code++;
clr->tmp[tidx] = value_continuation_new( clr, l, r );
printf( "\nnew continuation %d <- (%04lx %04lx %04lx)", tidx,
        VALUE_LONG(clr->tmp[tidx]), VALUE_LONG(l), VALUE_LONG(r) );
#endif
