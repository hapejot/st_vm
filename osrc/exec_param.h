#ifndef _EXEC_PARAM_H
#define _EXEC_PARAM_H
                        VALUE v = *code++;
                        if( v.u.v.kind == KIND_TREF ) {
                            param[params] = clr->tmp[v.u.v.idx];
                        }
                        else {
                            param[params] = v;
                        }
                        printf( " %d %04lx %d", params, param[params].u.l,
                                v.u.v.kind );
                        params++;
#endif
