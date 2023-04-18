#include "utils.h"

#include <malloc.h>
#include <stdlib.h>

vector_t *vector_new() {
    vector_t *result = (vector_t *) malloc(sizeof(vector_t));
    if (result == NULL) 
        return NULL;
    result->_cap = 1;
    result->_elements = (void**) malloc(result->_cap * sizeof(void *));
    if (result->_elements == NULL) {
        free(result);
        return NULL;
    }
    result->_len = 0;

    return result;
}

void vector_push(vector_t *vec, void *el) {
    if (vec->_len < vec->_cap) {
        vec->_elements[vec->_len] = el;
        vec->_len++;
        return;
    }

    vec->_cap *= 2;
    vec->_elements = realloc(vec->_elements, vec->_cap * sizeof(void*));
    if (vec->_elements == NULL) {
        fprintf(stderr, "vector push: error when allocating vector with capacity %ld\n", vec->_cap);
        exit(-1);
    }
    vec->_elements[vec->_len] = el;
    vec->_len++;
}

void *vector_get(vector_t* vec, size_t i) {
    if (i < vec->_len) {
        return vec->_elements[i];
    }
    return NULL;
}

size_t vector_len(vector_t *vec) {
    return vec->_len;
}

void *vector_pop(vector_t *vec) {
    if (vec->_len > 0) {
        return vec->_elements[--vec->_len];
    }
    return NULL;
}

void vector_free(vector_t *vec) {
    free(vec->_elements);
    free(vec);
}

void vector_print(vector_t *vec) {
    printf("[");
    if (vec->_len >= 1) {
        printf("%d", vector_get(vec, 0));
        for(size_t i = 1; i < vec->_len; i++) {
            printf(", %d", vector_get(vec, i));
        }
    }
    printf("]\n");
}
