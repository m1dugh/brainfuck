#ifndef BF_UTILS_H
#define BF_UTILS_H

#include <stddef.h>

typedef struct
{
    size_t _cap;
    size_t _len;
    void **_elements;
} vector_t;

typedef enum token_type
{
    COMMA = ',',
    OPENING_BRACKET = '[',
    CLOSING_BRACKET = ']',
    LEFT_SHIFT = '<',
    RIGHT_SHIFT = '>',
    PLUS = '+',
    MINUS = '-',
    DOT = '.'
} token_type_t;

vector_t *vector_new();

size_t vector_len(vector_t *);

void vector_push(vector_t *, void *);

void *vector_get(vector_t *, size_t);

void vector_free(vector_t *);

void *vector_pop(vector_t *);

void vector_print(vector_t *);

#endif // !BF_UTILS_H
