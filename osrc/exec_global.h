#ifndef _EXEC_GLOBAL_H
#define _EXEC_GLOBAL_H
                        VALUE t = *code++;
                        VALUE g = _global( *code++ );
                        uint_t tidx = t.u.v.idx;
                        printf( "\nhandling global var %d <- %lx", tidx,
                                g.u.l );
                        clr->tmp[tidx] = g;
#endif
