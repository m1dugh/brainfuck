#ifndef BF_VISITOR_H
#define BF_VISITOR_H

#include <stddef.h>
#include "parser.h"
#include "utils.h"

#define STACK_SIZE 10000

typedef struct
{
    char array[10000];
    size_t current;
} visitor_context_t;

visitor_context_t *context_new();

void visit_plus(visitor_context_t *context);
void visit_minus(visitor_context_t *context);
void visit_prompt(visitor_context_t *context);
void visit_print(visitor_context_t *context);
void visit_left(visitor_context_t *context);
void visit_right(visitor_context_t *context);

void visit_loop(visitor_context_t *context, vector_t *children);

void visit_token(AST *ast, visitor_context_t *context);

void visit(AST *global);

#endif /*!BF_VISITOR_H*/
