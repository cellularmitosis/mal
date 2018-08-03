#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Debian users: apt-get install libpcre3-dev
#include <pcre.h>

char* patterns[] = {
    "[\\s,]*",
    "~@",
    "[\\[\\]{}()'`~^@]",
    "\"(?:\\\\.|[^\\\"])*\"",
    ";.*",
    "[^\\s\\[\\]{}('\"`,;)]*"
};

//pcre_compile();

void tokenize(char *s) {

}

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

// evaluate a line of input.
char* EVAL(char *buf) {
    // for now, just echo back the input.
    return buf;
}

// print the evaluated output.
void PRINT(char *buf) {
    printf("%s\n", buf);
}

int main(void) {
    printf("%s\n", patterns[0]);
    printf("%s\n", patterns[1]);
    printf("%s\n", patterns[2]);
    printf("%s\n", patterns[3]);
    printf("%s\n", patterns[4]);
    printf("%s\n", patterns[5]);
    
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
