#ifndef BF_PARSER_H
#define BF_PARSER_H

#include "utils.h"


typedef struct {
    vector_t* children;
    token_type_t token;
} AST;

AST* ast_new(token_type_t);

vector_t* ast_from(vector_t *, size_t *start);

void ast_free(AST *);

AST *build_ast(vector_t *);

#endif /*!BF_PARSER_H*/
