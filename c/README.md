# Implementing "mal" (make-a-lisp) in C

Assumptions:
- You have `gcc` installed
- You are using a bash-like shell

Follow [the guide](https://github.com/kanaka/mal/blob/master/process/guide.md).


## step0_repl

Start by:
- forking the [mal](https://github.com/kanaka/mal) repo
- deleting the existing `c` directory (`rm -rf c`)
- creating a new (empty) `c` directory (`mkdir c`)

Navigate to the `c` directory:

```
$ cd c
```

Create the `run` file:

```
#!/bin/bash
exec $(dirname $0)/${STEP:-stepA_mal} "${@}"
```

Make it executable:

```
$ chmod +x run
```

Start with a trivial `step0_repl.c` file:

```c
#include <stdlib.h>

int main(void) {
	return EXIT_SUCCESS;
}
```

Check that it compiles and that you can run the compiled binary:

```
$ gcc step0_repl.c
$ ./a.out
```

Now let's create a simple `Makefile`:

```make
step0_repl: step0_repl.c
	gcc -Wall -Werror -o step0_repl step0_repl.c

clean:
	rm -f step0_repl

.PHONY: clean
```

(Note that those need to be actual tab characters, not spaces)

Try it out:

```
$ make
$ ./step0_repl
```

Assuming that all worked, let's implement an "echo" repl.

Here is our `READ` function.  We attempt to read one line of input into the buffer.

```c
// read a line of input to evaluate.
char* READ(char *buf, size_t limit) {
    // prompt the user for input:
    printf("user> ");

    // while we haven't exceeded 'limit':
    for(size_t i = 0; i < limit; i++) {
        // read a char from stdin
        int ch = getchar();
        // if we've reached EOF or end-of-line...
        if (ch == EOF || ch == '\n') {
            // null-terminate the string...
            buf[i] = '\0';
            // and return a pointer to the string, or NULL on error.
            if (ferror(stdin)) {
                return NULL;
            } else {
                return buf;
            }
        } else {
            // otherwise, store the char into the buffer.
            buf[i] = (char)ch;
        }
    }
    // overflow: we reached 'limit' before finding a newline; return NULL.
    return NULL;
}
```

Here is our trivial "eval" function.  We simply return the input as the output.

```c
// evaluate a line of input.
char* EVAL(char *buf) {
    // for now, just echo back the input.
    return buf;
}
```

And the print function:

```c
// print the evaluated output.
void PRINT(char *buf) {
    printf("%s\n", buf);
}
```

Finally, we tie them together in `main`:

```c
int main(void) {
    // declare an input buffer:
    size_t inbuf_size = 1024 + 1;
    char inbuf[inbuf_size];

    // run the repl until we hit EOF:
    while (!feof(stdin)) {
        PRINT(EVAL(READ(inbuf, inbuf_size)));
    }

    // determine the appropriate exit status:
    if (ferror(stdin)) {
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}
```

Build it:

```
$ make
```

Try it out (hit CTRL+d to exit the repl):

```
$ ./step0_repl
user> hello
hello
```
