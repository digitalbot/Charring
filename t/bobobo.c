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
#include <string.h>
#include <assert.h>
#include <time.h>

#include "../charring.h"

char *gen();

int main(int argc, char *argv[]) {
    srand(time(NULL));
    Charring *chrr = new_charring(10);
    
    while (1) {
        char *c = gen();
        printf("%s", c);
        add_char(chrr, c);
        char *joined = join_char(chrr);
        
        if (! strcmp(joined, "ボボボーボ・ボーボボ")) {
            // printf("\n\n\n--------------------\n");
            // printf("%s\n", joined);
            del_joined_char(joined);
            break;
        }
            
        del_joined_char(joined);
    }
    printf("\n");
    return 0;
}

char *gen() {
    char *bo = "ボ";
    char *pyphen = "ー";
    char *point = "・";
    char *seed[] = { bo, pyphen, point };
    
    int n = rand() % 3;
    return seed[n];
}
