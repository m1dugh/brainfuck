#include <stdlib.h>
#include "lexer.h"

vector_t *tokenize(FILE *file)
{
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

    return tokens;
}
