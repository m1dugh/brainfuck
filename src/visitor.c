#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "visitor.h"

visitor_context_t *context_new() {
    return (visitor_context_t *) malloc(sizeof(visitor_context_t));
}

void visit_plus(visitor_context_t *context) {
    context->array[context->current]++;
}

void visit_minus(visitor_context_t *context) {
    context->array[context->current]--;
}

void visit_prompt(visitor_context_t *context) {
    char value;
    scanf("%c", &value);
    context->array[context->current] = value;
}
void visit_print(visitor_context_t *context) {
    printf("%c", context->array[context->current]);
}
void visit_right(visitor_context_t *context) {
    if(context->current < STACK_SIZE - 1) {
        context->current++;
    } else {
        fprintf(stderr, "Exceeded max number of registers\n");
        exit(-1);
    }
}
void visit_left(visitor_context_t *context) {
    if(context->current > 0) {
        context->current--;
    } else {
        fprintf(stderr, "Cannot access registers < 0\n");
        exit(-1);
    }
}

void visit_loop(visitor_context_t *context, vector_t *children) {
    while(context->array[context->current]) {
        for(size_t i = 0; i < vector_len(children); i++) {
            AST *el = (AST *) vector_get(children, i);
            visit_token(el, context);
        }
    }
}

void visit_token(AST* ast, visitor_context_t *context) {
    switch (ast->token) {
        case COMMA:
            visit_prompt(context);
            break;
        case DOT:
            visit_print(context);
            break;
        case OPENING_BRACKET:
            visit_loop(context, ast->children);
            break;
        case PLUS:
            visit_plus(context);
            break;
        case MINUS:
            visit_minus(context);
            break;
        case LEFT_SHIFT:
            visit_left(context);
            break;
        case RIGHT_SHIFT:
            visit_right(context);
            break;
        default:;
    }
}

void visit(AST *global) {
    visitor_context_t *context = context_new();
    for(size_t i = 0; i < vector_len(global->children); i++) {
        AST *el = vector_get(global->children, i);
        visit_token(el, context);
    }
}
