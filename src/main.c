#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef enum token_type {
    COMMA,
    OPENING_BRACKET,
    CLOSING_BRACKET,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    PLUS,
    MINUS
} token_type_t;

int main(int argc, char**argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: brainfuck <file>.bf\n");
        exit(-1);
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL) {
        fprintf(stderr, "File %s does not exist\n", argv[1]);
        exit(-1);
    }

    vector_t *vec = vector_new();

    while(!feof(file)) {
        int ch = fgetc(file);
        switch (ch) {
            case ',':
                vector_push(vec, COMMA);
                break;
            default:
                fprintf(stderr, "Unknown character %c\n", ch);
                exit(-1);
        };
    }

    vector_free(vec);
    fclose(file);

    return 0;
}
