/**
 * Charring - A character ring buffer library for c
 * The MIT License (MIT)
 *
 *  *Copyright (c) 2014 Kosuke Nakamura a.k.a digitalbot.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "charring.h"

// private ---
char* validate_get_char_(Charring*, int32_t);
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
    if (c == NULL) {
        fprintf(stderr, "[ERROR] Can't add NULL character\n");
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
    char *res = validate_get_char_(r, idx);
    if (strcmp(res, "ok")) {
        return EXIT_FAILURE;
    }
    return r->ring[(r->head + idx) % r->capacity]->size;
}

char* get_char(Charring *r, int32_t idx) {
    char *res = validate_get_char_(r, idx);
    if (strcmp(res, "ok")) {   // res != ok
        return res;
    }
    return r->ring[(r->head + idx) % r->capacity]->s;
}

char *validate_get_char_(Charring *r, int32_t idx) {
    if (r == NULL) {
        return "[ERROR] not allocated";
    }
    if (r->tail == -1) {
        return "[ERROR] no entry";
    }
    if (idx < 0) {
        return "[ERROR] index must be unsigned value";
    }
    if (idx >= r->length) {
        return "[ERROR] over index";
    }
    return "ok";
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

// TODO: too expensive
char *join_char(Charring *r) {
    if (r ==NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return NULL;
    }

    size_t total = 1;   // this '1' is tail of string '\0' size;
    for (int i = 0; i < r->length; i++) {
        total += r->ring[i]->size - 1;
    }
    
    char *string = (char *)calloc(1, total);   // do not use malloc
    if (string == NULL) {
        fprintf(stderr, "[ERROR] Can't allocate memmory\n");
        return NULL;
    }
    
    for (int i = 0; i < r->length; i++) {
        strcat(string, get_char(r, i));
    }
    
    return string;
}

// TODO: i do not wanna free by hand power.
void del_joined_char(char *s) {
    if (s == NULL) {
        fprintf(stderr, "[ERROR] not allocated\n");
        return;
    }
    free(s);
}
