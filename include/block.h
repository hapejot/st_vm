#ifndef _BLOCK_H
#define _BLOCK_H
typedef struct block *BLOCK;

struct block {
    bool active;
    VALUE method;
    VALUE parent_block;
    VALUE ref;  // code ptr
    uint length; // lenght of the code
    // CLOSURE clr; // 
    uint temps;
    VALUE tmp[10];
};
#endif
