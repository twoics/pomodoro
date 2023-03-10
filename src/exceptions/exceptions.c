#include <stdio.h>
#include <stdlib.h>

#define EXIT_CODE (-1)
#define SEPARATOR " -------------"

void fatal_exit(char* message, const char* func_name, int line_number) {
    fprintf(stderr,
            "%s\n| FATAL ERROR |\n%s\nFUNC: %s\nLINE: %d\nMESSAGE: %s",
            SEPARATOR,
            SEPARATOR,
            func_name,
            line_number,
            message
    );
    exit(EXIT_CODE);
}

void exit_with_code(int code) {
    exit(code);
}