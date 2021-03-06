#ifndef _CONTINUATION_H
#define _CONTINUATION_H
/*
 * CONTINUATION
 *
 *
 *
 */
typedef struct continuation * CONTINUATION;
struct continuation {
    bool active;
    VALUE ref; // code reference to continue
    VALUE tref; // temporary variable position to store results
    CLOSURE closure;
};
#endif
