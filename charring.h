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

#ifndef CHARRING_H
#define CHARRING_H
#include <stdint.h>

struct SizedString {
    char *s;
    size_t size;  // contained \0
};
typedef struct SizedString SizedString;

struct Charring {
    int32_t capacity;
    int32_t length;
    int32_t head;
    int32_t tail;
    SizedString **ring;
};
typedef struct Charring Charring;


Charring *new_charring(int32_t);
void del_charring(Charring*);
int add_char(Charring*, const char*);
char* get_char(Charring*, int32_t);
char *join_char(Charring*);
void del_joined_char(char*);


#endif
