#include <stdint.h>
#include <stdio.h>
#include "dict.h"

/*----------------------------------- types -----------------------------------*/
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

typedef struct 
{
    void *key;
    dictEntry *next;
} dictEntryNoValue;

/*----------------------------------- private prototypes -----------------------------------*/

static int _dictInit(dict *d, dictType *type);

/*----------------------------------- hash functions -----------------------------------*/

static uint8_t dict_hash_function_seed[16];

void dictSetHashFunctionSeed(uint8_t *seed)
{
    memcpy(dict_hash_function_seed, seed, sizeof(dict_hash_function_seed));
}

uint8_t *dictGetHashFunctionSeed(void)
{
    return dict_hash_function_seed;
}

uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k);
uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k);

/* Reset hash table parameters already initialized with _dictInit() */
static void _dictReset(dict *d, int htidx)
{
    d->ht_table[htidx] = NULL;
    d->ht_size_exp[htidx] = -1;
    d->ht_used[htidx] = 0;
}

/* Create a new hash table */
dict *dictCreate(dictType *type)
{
    size_t metasize = type->dictMetadataBytes ? type->dictMetadataBytes(NULL) : 0;
    dict *d = zmalloc(sizeof(*d) + metasize);
    if (metasize >0)
    {
        memset(dictMetadata(d), 0, metasize);
    }
    _dictInit(d, type);
    return d;
}

/* Initialize the hash table */
int _dictInit(dict *d, dictType *type)
{
    _dictReset(d, 0);
    _dictReset(d, 1);
    d->type = type;
    d->rehashidx = -1;
    d->pauserehash = 0;
    d->pauseAutoResize = 0;
    return DICT_OK;
}

void dict_test()
{
    struct dictEntry dict;
    printf("%zu\n", sizeof(dict.v));
}