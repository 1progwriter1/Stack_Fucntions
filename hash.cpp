#include <stdio.h>
#include "assert.h"
#include "hash.h"

int sizehash = 8;
static unsigned long long *hash_data = (unsigned long long *) calloc (sizehash, sizeof (unsigned long long));

unsigned long long HashCount(const Stack *stk) {

    assert(stk);

    unsigned long long bitessum = 5381;
    const int NUM_OF_BITES = stk->capacity * sizeof (Elem_t) + 2 * sizeof (canary_t);
    char *ptr = (char *) stk->data - sizeof (canary_t);

    for (size_t i = 0; i < NUM_OF_BITES; i++) {
        bitessum = 33 * bitessum + *ptr++;
    }

    return bitessum;
}

enum Result HashCreate(Stack *stk, int id) {

    if (id >= sizehash) {
         sizehash *= 2;
        hash_data = (unsigned long long *) realloc (hash_data, sizehash * sizeof (unsigned long long));
        if (!hash_data)
            return NO_MEMORY;
    }
    hash_data[id] = HashCount(stk);
    return SUCCESS;
}

void clean() {
    free(hash_data);
}

void HashClean(int id) {
    hash_data[id] = 0;
}

int HashCheck(const Stack *stk) {

    assert(stk);

    return hash_data[stk->id] == HashCount(stk);
}
