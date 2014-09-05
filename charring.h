#ifndef CHARRING_H
#define CHARRING_H

struct Charring {
    uint32_t capacity;
    uint32_t length;
    uint32_t head;
    uint32_t tail;
    uint64_t cur;
    void **ring;
};
typedef struct Charring Charring;

Charring *new_charring(uint32_t);
void del_charring(Charring*);
int add_char(Charring*, const char*);
char* get_char(Charring*, uint32_t);


#endif
