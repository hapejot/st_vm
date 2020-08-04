



entry send:
    lookup class
    identify method
    create method closure
    assign object to closure
    pass arguments to closure
    get first continuation
    assign continuation to closure
    activate closure (at continuation)





Continuation: basically a pointer to the next address that should be executed.


Closure: Keeps the data of all local values and variables. This includes intermediate
results of partially evaluated expressions.

Definition of the instructions
===

Code|Description
-|-
method <name> <filler> <class>|start method implementation
tvar <name>|temporary variable declaration reserves space in the closure
pvar <pos> <name>|gives a positional parameter a name.
ivar <name>|instance variables need to be declared explicitly in each method implementation
end|ends an implementation. Is no real opcode, it is just there to control the assembler
registers|these are global to the interpreter
r0|register contains current result of operation
temporaries|these are local to the method execution and are keept local in a closure
t0|the first unnamed temporary, that is automatically allocated
"label":|is an address local to the method given in a relative address to the start of the method.
mkcont|creates a continuation based on the current closure and the address of a label.
param|adds a parameter to the next "send"
send|is looking up the apropriate implementation for the method selector and the current reciever and calls it.





From Appels paper (1989)
---

when one function is nested inside another, the inner functin may refer to variables bound in the outer function.
a compiler for a language where function nesting is permitted must have a mechanism for access to these variables.
the problem is more complicated in languages with higher-order functions, where the inner function can be called after the outer function has returned. (like Haskell or Blocks in Smalltalk)
the usual implementation technique uses a "closure" data structure:
a record containing the free variabels of the inner function as well as a pointer to its machine code.
a pointer to this record is made available to the machine code while it executes so that the free varaibles are accessible.
by putting the code-pointer at a fixed offset of the record, users of the function need not know the format of the record or even its size in order to call the function.
(does that mean the function has to create the closure records? Who else will know the size and structure then?)

in fact, several functions can be rpresented by a single closure record containing the union of their free variables and code pointers.
a closure record is necessary only for a function that "escapes" -- some of its call sites are unknown because it is passed as an argument, stored into a data structure, or returned as a result of a function-call.
a call of an escaping function is implemented by extracting the code pointer from the closure record and jumping to the function with the closure record as one of its arguments.

the closure of a "known" function (whose every call site is known at compile-time) need not be implemented as a record.
instead, the free variables can be added as extra arguments to the function.
a call of a known function must arrange to pass along the appropriate variables to the function.
this implmentation of closures is intended to produce efficient code for loops.

some functions escape and are also called from known sites.
these can be split into two functions, where the escaping function is defined in terms of the known one, in the hope that the known calls will execute more efficiently.

