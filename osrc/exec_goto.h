#ifndef _EXEC_GOTO_H
#define _EXEC_GOTO_H

VALUE t = *code++; // ref to temp of continuation
VALUE tv = *code++; // ref to target value 
if(t.u.v.kind == KIND_TREF) {
    t = clr->tmp[t.u.v.idx];
}
CONTINUATION cc = _continuation( t );
if(cc){
printf(" continuation %04lx -> %p", t.u.l, (void*)cc );
uint_t idx_s = tv.u.v.idx;
uint_t idx_t = cc->tref.u.v.idx;
printf(" from T%d to T%d", idx_s, idx_t);
cc->closure->tmp[idx_t] = clr->tmp[idx_s];
clr = cc->closure;
printf( "\nNEW REF: %04lx", cc->ref.u.l );
code = value_code_ptr( cc->ref );
}
else{
    printf("\nNO CONTINUATION");
    return;
}
#endif
