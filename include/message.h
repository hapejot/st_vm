#ifndef _MESSAGE_H
#define _MESSAGE_H
struct message {
    VALUE obj;
    VALUE cont;
    VALUE argc;
    VALUE args[10];
};
#endif
