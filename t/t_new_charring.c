#include <stdio.h>
#include <stdlib.h>
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
    Charring *chrr = new_charring(5);

    add_char(chrr, "100");
    add_char(chrr, "200");
    add_char(chrr, "300");
    add_char(chrr, "400");
    for (int i = 0; i < chrr->length; i++) {
        printf("%s\n", get_char(chrr, i));
    }
    add_char(chrr, "500");
    for (int i = 0; i < chrr->length; i++) {
        printf("%s\n", get_char(chrr, i));
    }
    add_char(chrr, "600");
    add_char(chrr, "700");
    add_char(chrr, "800");
    add_char(chrr, "900");
    for (int i = 0; i < chrr->length; i++) {
        printf("%s\n", get_char(chrr, i));
    }

    del_charring(chrr);
}
