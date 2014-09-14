#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "../charring.h"

char *gen();

//ボボボーボ・ボーボボ 10
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
