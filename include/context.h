#ifndef _CONTEXT_H
#define _CONTEXT_H
struct context {
    CLOSURE clr;
    MESSAGE exec_msg;  // currently executed message
    VALUE ref;
    VALUE *code;
    // VALUE param[10];
    // uint_t params;
    MESSAGE tmp_msg; // scratch message to send
};
#endif
