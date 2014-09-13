#ifndef CHARRING_H
#define CHARRING_H

#include <stdint.h>

struct Charring {
    int32_t capacity;
    int32_t length;
    int32_t head;
    int32_t tail;
    void **ring;
};
typedef struct Charring Charring;

Charring *new_charring(int32_t);
void del_charring(Charring*);
int add_char(Charring*, const char*);
char* get_char(Charring*, int32_t);


#endif
