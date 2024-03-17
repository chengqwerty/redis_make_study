#define DICT_OK 0
#define DICT_ERR 1

typedef struct dictEntry dictEntry;
typedef struct dict dict;

typedef struct dictType {
    uint64_t (*hashFunction)(const void *key);
    void *(*keyDup)(dict *d, const void *key);
    void *(*valDup)(dict *d, const void *obj);
    int (*keyCompare)(dict *d, const void *key1, const void *key2);
    void (*keyDestructor)(dict *d, void *key);
    void (*valDestructor)(dict *d, void *obj);
    int (*resizeAllowed)(size_t moreMem, double usedRatio);

    void (*rehashingStarted)(dict *d);
    void (*rehashingCompleted)(dict *d);
    size_t (*dictMetadataBytes)(dict *d);

    void *userdata;

    unsigned int no_value:1;
    unsigned int keys_are_odd:1;
} dictType;

struct dict {
    dictType *type; 

    dictEntry **ht_table[2];
    unsigned long ht_used[2];

    long rehashidx; /* rehashing not in progress if rehashidx == -1 */

    int16_t pauserehash;
    signed char ht_size_exp[2];
    int16_t pauseAutoResize;
    void *metadata[];
};

#define dictMetadata(d) (&(d)->metadata)

/* API */
dict *dictCreate(dictType *type);

void dict_test(void);