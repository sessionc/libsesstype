Coding style
============

This document is a guideline for writing code that is clear, consistent
and maintainable. Consistency with this style guide is important, but if
there are aspects of the coding style not covered by this style guide,
make a sensible judgement, and consider adding the judgement to this
document.

Most of the rules here are adapted from various sources, in particular,
OOP-related items are from the *Google C++ style guide*, and most of the
language-neutral items are from the *Linux Kernel style guide*.

Indentation and Spacing
-----------------------

Use space to indent and no tabs. For *C code*: Use 4 space indentation.
For *C++ code*: Use 4 space indentation, `public:`, `protected:`,
`private:` should be indented 2 space.

### Line wrapping

The limit on the length of lines is 80 columns, unless exceeding 80
columns significantly increases readability.

When you have a boolean expression that is longer than the standard line
length, be consistent in how you break up the lines.
Prefer `&&` at the end of the line and `||` at the beginning of line
and line conditions up in the same column.

No line should end in whitespace.

### Preprocessors

The hash mark `#` that starts a preprocessor directive should always
be at the beginning of the line.  Even when preprocessor directives
are within the body of indented code, the directives should start at
the beginning of the line.

### Braces placement

The preferred braces placement as shown by Kernighan and Ritchie, is
to put the opening brace last on the line, and put the closing brace
first. The open curly brace is always at the end of the same line as
the last parameter.  The close curly brace is either on the last line
by itself or (if other style rules permit) on the same line as the
open curly brace.

The open parenthesis is always on the same line as the function name.
There is never a space between the function name and the open
parenthesis.

There is never a space between the parentheses and the parameters.
There should be a space between the close parenthesis and the open
curly brace.

    if (x is true) {
        we do y
    }

This applies to all non-function statement blocks (`if`, `switch`, `for`,
`while`, `do`).  E.g.:

    switch (action) {
    case GLOBAL:
        return "global";
    case LOCAL:
        return "local";
    case PARAM:
        return "parameterised";
    default:
        return NULL;
    }

However, there is one special case, namely functions: they have the
opening brace at the beginning of the next line because you cannot
nest functions in C.

    int function(int x)
    {
        // function body
    }

Note that the closing brace is empty on a line of its own, _except_
in the cases where it is followed by a continuation of the same
statement, ie a `while` in a `do`-statement or an `while` in an
`if`-statement, like this:

    do {
        // Loop body.
    } while (condition);

and

    if (x == y) {
        // ..
    } else if (x > y) {
        // ...
    } else {
        // ....
    }

Do not unnecessarily use braces where a single statement will do.

    if (condition)
        action();

and

    if (condition)
        do_this();
    else
        do_that();

This does not apply if only one branch of a conditional statement is
a single statement; in the latter case use braces in both branches:

    if (condition) {
        do_this();
        do_that();
    } else {
        otherwise();
    }

### Comments and Documentation

Use `///` style commenting, and for header files add doxygen style
documentations for each of the major class and functions.

Scripting
---------

Always use a `#!/path/to/interpreter` line in the first line of the
script.  This allows scripts to be treated as an executable object
file even without a clear file extension on the file name

Shell: prefer `/bin/sh` because it is the most commonly available shell
and users generally do not have have environment-specific configuration
for it. If the task is more complicated than `sh` can handle, consider
using a real scripting language (like Python) instead.

Make sure exit on error is turned on, and optionally, verbose
execution mode (prints out all executed commands) by `set -ex`. The
combination avoids a lot of silly shell scripting errors.

    #!/bin/sh
    set -ex

Memory management
-----------------

*Memory ownership*: Caller of `malloc`/`new` is responsible for
`free`/`delete` of allocated memory.  Exception for pointers that are
passed to a container as part of a data structure (for example, storing
pointer of `Role`s in a `Tree` class), then the container is responsible
for managing the memory of the pointer.

*Constructor*: Unless there is a good reason, a C++ constructor should
chain the constructors of member variables rather than calling them in
the constructor body. Chained constructors are guaranteed to be called
before anything else in the object.
