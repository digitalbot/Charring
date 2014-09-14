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

#include "../charring.h"

void t_new_charring();
void t_add_char();

int main(int argc, char *argv[]) {
    t_new_charring();
    t_add_char();
    return EXIT_SUCCESS;
}

void t_new_charring() {
    int capacity = 10;
    Charring *chrr = new_charring(capacity);
    assert(chrr);
    del_charring(chrr);
    return;
}

void t_add_char() {
    Charring *chrr = new_charring(3);
    
    assert(chrr->length == 0);
    assert(strcmp(get_char(chrr, 0), "[ERROR] no entry") == 0);
    
    add_char(chrr, "100");
    assert(strcmp(get_char(chrr, 0), "100") == 0);
    assert(chrr->length == 1);
    assert(strcmp(get_char(chrr, 1), "[ERROR] over index") == 0);
    
    add_char(chrr, "200");
    add_char(chrr, "300");
    assert(strcmp(get_char(chrr, 0), "100") == 0);
    assert(strcmp(get_char(chrr, 1), "200") == 0);
    assert(strcmp(get_char(chrr, 2), "300") == 0);
    assert(strcmp(get_char(chrr, 3), "[ERROR] over index") == 0);
    assert(strcmp(get_char(chrr, 4), "[ERROR] over index") == 0);
    assert(strcmp(get_char(chrr, 10), "[ERROR] over index") == 0);
    assert(strcmp(get_char(chrr, -1), "[ERROR] index must be unsigned value") == 0);
    assert(chrr->length == 3);
    
    add_char(chrr, "400");
    assert(strcmp(get_char(chrr, 0), "200") == 0);
    assert(strcmp(get_char(chrr, 1), "300") == 0);
    assert(strcmp(get_char(chrr, 2), "400") == 0);
    assert(chrr->length == 3);
    
    add_char(chrr, "500");
    add_char(chrr, "600");
    add_char(chrr, "700");
    add_char(chrr, "800");
    add_char(chrr, "900");
    assert(strcmp(get_char(chrr, 0), "700") == 0);
    assert(strcmp(get_char(chrr, 1), "800") == 0);
    assert(strcmp(get_char(chrr, 2), "900") == 0);

    del_charring(chrr);
}
