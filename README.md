NAME
=====

Charring - A character ring buffer library for c-language.


Usage
-----

This library produces simple functions below.  

And you can use freely these functions without any issues.  

```c
Charring *new_charring(int32_t);
void del_charring(Charring*);
int add_char(Charring*, const char*);
char* get_char(Charring*, int32_t);
char *join_char(Charring*);
void del_joined_char(char*);
```

### Basic

```c
int capacity = 5;
Charring *chrr = new_charring(capacity);
add_char(chrr, "hoge");
add_char(chrr, "foo");
add_char(chrr, "bar");
add_char(chrr, "baz");
add_char(chrr, "fuga");
for (int i = 0; i < chrr->length; i++) {
    printf("%s\n", get_char(chrr, i));
    // => hoge
    // => foo
    // => bar
    // => baz
    // => fuga
}
del_charring(chrr);
```

It's over.  

You have to call `del_charring()` to avoid memory leaks.


#### This is a Ring Buffer

```c
int capacity = 3;
Charring *chrr = new_charring(capacity);
add_char(chrr, "hoge");
add_char(chrr, "foo");
add_char(chrr, "bar");
add_char(chrr, "baz");
add_char(chrr, "fuga");
for (int i = 0; i < chrr->length; i++) {
    printf("%s\n", get_char(chrr, i));
    // => bar
    // => baz
    // => fuga
}
del_charring(chrr);
```

You do not have to care buffer size. You may only `add`.


### Join Characters

```c
int capacity = 10;
Charring *chrr = new_charring(capacity);
add_char(chrr, "This");
add_char(chrr, "Is");
add_char(chrr, "A");
add_char(chrr, "Pen.");

char *joined = join_char(chrr);
printf("%s\n", joined);
// => ThisIsAPen.

del_joined_char(chrr);
del_charring(chrr);
```

`join_char()` and `del_joined_char()` are pare functions.  

Because `join_char()` return `malloc`ed character. you have to call `free`.


### tips

You can use `length` property like a above examples.  

You do not have to care "number of added".


Know issues & enhancement
-----

- more fast

- more performance

- try to use [sds](https://github.com/antirez/sds) library.


LICENSE
-----
Copyright (C) Kosuke Nakamura a.k.a digitalbot.

This software is released under the MIT License, see LICENSE.txt.

