#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "charring.h"

// private ---
int validate_get_char(Charring*, int32_t);
// -----------   


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
    new->ring = (SizedString **)calloc(capacity, sizeof(SizedString *));
    return new;
}

int add_char(Charring *r, const char *c) {
    if (r == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return EXIT_FAILURE;
    }
    SizedString *ss = (SizedString *)malloc(sizeof(SizedString));
    if (ss == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return EXIT_FAILURE;
    }
        
    ss->size = strlen(c) + 1;
    ss->s = (char *)malloc(ss->size);
    if (ss->s == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return EXIT_FAILURE;
    }
    strcpy(ss->s, c);

    if (r->length == r->capacity) {
        r->head = ++r->head % r->capacity;
    }
    r->tail = ++r->tail % r->capacity;
    r->length = (r->length < r->capacity) ? r->length + 1 : r->capacity;
    
    if (r->ring[r->tail] != NULL) {
        free(r->ring[r->tail]->s);
        free(r->ring[r->tail]);
    }
    
#ifdef DEBUG
    printf("length: %d, head %d, tail: %d, data: %s\n", r->length, r->head, r->tail, t);
#endif
    
    r->ring[r->tail] = ss;
    return r->tail;
}

size_t get_charsize(Charring *r, int32_t idx) {
    if (validate_get_char(r, idx) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    return r->ring[(r->head + idx) % r->capacity]->size;
}

char* get_char(Charring *r, int32_t idx) {
    if (validate_get_char(r, idx) == EXIT_FAILURE) {
        return NULL;
    }
    return r->ring[(r->head + idx) % r->capacity]->s;
}

int validate_get_char(Charring *r, int32_t idx) {
    if (r == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return EXIT_FAILURE;
    }
    if (r->tail == -1) {
        fprintf(stderr, "[ERROR] no entry\n");
        return EXIT_FAILURE;
    }
    if (idx < 0) {
        fprintf(stderr, "[ERROR] index must be unsigned value");
        return EXIT_FAILURE;
    }
    if (idx >= r->length) {
        fprintf(stderr, "[ERROR] over index");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void del_charring(Charring *r) {
    if (r == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return;
    }
    for (int i = 0; i < r->length; i++) {
        if (r->ring[i] != NULL) {
            free(r->ring[i]->s);
            free(r->ring[i]);
        }
    }
    free(r->ring);
    free(r);
}

char *join_char(Charring *r) {
    if (r ==NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return NULL;
    }

    size_t total = 1;
    for (int i = 0; i < r->length; i++) {
        total += r->ring[i]->size - 1;
    }
    
    char *string = (char *)calloc(1, total);
    if (string == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return NULL;
    }
    
    for (int i = 0; i < r->length; i++) {
        strcat(string, get_char(r, i));
    }
    
    return string;
}

// TODO: too expensive
void del_joined_char(char *s) {
    if (s == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return;
    }
    free(s);
}
