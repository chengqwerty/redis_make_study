#include <stdint.h>
#include <stdio.h>
#include "dict.h"

struct dictEntry
{
    void *val;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
        double d;
    } v;
    struct dictEntry *next;
};


void dict_test()
{
    struct dictEntry dict;
    printf("%zu\n", sizeof(dict.v));
}