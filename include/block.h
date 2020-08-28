#ifndef _BLOCK_H
#define _BLOCK_H
typedef struct block *BLOCK;

struct block {
    bool active;
    VALUE ref;  // code ptr
    // CLOSURE clr; // 
    uint temps;
    VALUE tmp[10];
};
#endif
