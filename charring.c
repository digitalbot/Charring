#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "charring.h"

Charring *new_charring(int32_t capacity) {
    Charring *new = (Charring *)malloc(sizeof(Charring));
    if (new == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return NULL;
    }

    new->capacity = capacity;
    new->length   = 0;
    new->head = 0;
    new->tail = -1;
    new->ring = (void **)calloc(capacity, sizeof(void *));
    return new;
}

int add_char(Charring *r, const char *c) {
    if (r == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return EXIT_FAILURE;
    }
    char *t = (char *)malloc(strlen(c) + 1);
    if (t == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return EXIT_FAILURE;
    }
    strcpy(t, c);

    if (r->length == r->capacity) {
        r->head = ++r->head % r->capacity;
    }
    r->tail = ++r->tail % r->capacity;
    r->length = (r->length < r->capacity) ? r->length + 1 : r->capacity;
    
    if (r->ring[r->tail] != NULL) {
        free(r->ring[r->tail]);
    }
    
#ifdef DEBUG
    printf("length: %d, head %d, tail: %d, data: %s\n", r->length, r->head, r->tail, t);
#endif
    
    r->ring[r->tail] = t;
    return r->tail;
}

char* get_char(Charring *r, int32_t idx) {
    if (r->tail == -1) {
        return "[ERROR] no entry";
    }
    if (idx < 0) {
        return "[ERROR] index must be unsigned value";
    }
    if (idx >= r->length) {
        return "[ERROR] over index";
    }
    return r->ring[(r->head + idx) % r->capacity];
}

void del_charring(Charring *r) {
    if (r == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return;
    }
    for (int i = 0; i < r->capacity; i++) {
        if (r->ring[i] != NULL) {
            free(r->ring[i]);
        }
    }
    free(r->ring);
    free(r);
}
