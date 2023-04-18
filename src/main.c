#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"
#include "visitor.h"

#define STACK_SIZE 10000

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: brainfuck <file>.bf\n");
        exit(-1);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "File %s does not exist\n", argv[1]);
        exit(-1);
    }

    vector_t *tokens = vector_new();

    while (!feof(file))
    {
        int ch = fgetc(file);
        switch (ch)
        {
            case ',':
                vector_push(tokens, (void *)COMMA);
                break;
            case '+':
                vector_push(tokens, (void *)PLUS);
                break;
            case '[':
                vector_push(tokens, (void *)OPENING_BRACKET);
                break;
            case ']':
                vector_push(tokens, (void *)CLOSING_BRACKET);
                break;
            case '-':
                vector_push(tokens, (void *)MINUS);
                break;
            case '>':
                vector_push(tokens, (void *)RIGHT_SHIFT);
                break;
            case '<':
                vector_push(tokens, (void *)LEFT_SHIFT);
                break;
            case '.':
                vector_push(tokens, (void *)DOT);
                break;
            case ' ':
            case '\n':
            case -1:
                break;
            default:
                fprintf(stderr, "Unknown character %d(%c)\n", ch, ch);
                exit(-1);
        };
    }

    AST *ast = build_ast(tokens);

    visit(ast);

    vector_free(tokens);
    fclose(file);

    return 0;
}
