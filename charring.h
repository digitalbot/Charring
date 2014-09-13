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
