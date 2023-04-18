#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"

AST *ast_new(token_type_t token)
{
    AST *result = (AST *)malloc(sizeof(AST));
    if (result == NULL)
    {
        return NULL;
    }

    result->children = vector_new();
    if (result->children == NULL)
    {
        free(result);
    }
    result->token = token;

    return result;
}

void ast_free(AST *ast)
{
    for (size_t i = 0; i < vector_len(ast->children); i++)
    {
        AST *element = vector_get(ast->children, i);
        free(element);
    }
    vector_free(ast->children);
    free(ast);
}

vector_t *ast_from(vector_t *tokens, size_t *start)
{
    vector_t *children = vector_new();
    if (children == NULL)
        return NULL;

    void *token_result;
    while ((token_result = vector_get(tokens, *start)) != NULL)
    {
        token_type_t token = (token_type_t)(size_t)token_result;
        *start = *start + 1;
        AST *child;
        switch (token)
        {
            case OPENING_BRACKET:
                child = (AST *)malloc(sizeof(AST));
                if (child == NULL)
                {
                    fprintf(stderr, "malloc error while allocating loop");
                    exit(-1);
                }
                child->token = token;
                child->children = ast_from(tokens, start);
                vector_push(children, child);
                break;
            case CLOSING_BRACKET:
                return children;
            default:
                child = ast_new(token);
                vector_push(children, child);
                break;
        };
    }
    return children;
}

AST *build_ast(vector_t *tokens)
{
    size_t index = 0;
    AST *result = ast_new((token_type_t)0);
    result->children = ast_from(tokens, &index);
    if (index != vector_len(tokens))
    {
        ast_free(result);
        return NULL;
    }
    else
    {
        return result;
    }
}
