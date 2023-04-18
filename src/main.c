#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
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

    vector_t *tokens = tokenize(file);

    AST *ast = build_ast(tokens);

    visit(ast);

    ast_free(ast);
    vector_free(tokens);
    fclose(file);

    return 0;
}
