#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "charring.h"

Charring *new_charring(uint32_t capacity) {
    Charring *new = (Charring *)malloc(sizeof(Charring));
    if (new == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return NULL;
    }

    new->capacity = capacity;
    new->length   = 0;
    new->cur  = 0;
    new->head = 0;
    new->tail = 0;
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

    r->tail = r->cur % r->capacity;
    r->length++;
    if (++r->cur > r->capacity) {
        r->head = r->head > r->capacity - 1 ? 0 : ++r->head;
        r->length = r->capacity;
    }

    r->ring[r->tail] = t;

    return r->tail;
}

char* get_char(Charring *r, uint32_t idx) {
    return idx < r->capacity ? (char *)r->ring[(r->head + idx) % r->capacity] : "[ERROR] over index";
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
    free(r);
}
