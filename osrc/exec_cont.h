#ifndef _EXEC_CONT_H
#define _EXEC_CONT_H
                        VALUE t = *code++;
                        uint_t tidx = t.u.v.idx;
                        VALUE l = *code++;
                        VALUE r = *code++;
                        printf( "\nnew continuation %d <- (%p %lx %lx)", tidx,
                                ( void * )clr, l.u.l, r.u.l );
                        clr->tmp[tidx] = _continuation_new( clr, l, r );
#endif
