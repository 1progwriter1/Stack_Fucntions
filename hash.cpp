#include <stdio.h>
#include "hash.h"
#include "assert.h"
#include "stack_values.h"
#include "config.h"

enum Result HashCtor(Hash *hsh, Stack *stk) {

    assert(hsh);
    assert(stk);

    hsh->bite_sum = Bitessum(stk);
    return SUCCESS;
}

enum Result HashDtor(Hash *hsh) {

    assert(hsh);

    hsh->bite_sum = -1;
    return SUCCESS;
}

unsigned long long Bitessum(Stack *stk) {

    assert(stk);

    long long int bitessum = 0;
    const int NUM_OF_BITES = stk->capacity * sizeof (Elem_t) + 2 * sizeof (canary_t);
    char *ptr = (char *)(stk->data - sizeof (canary_t) / sizeof (Elem_t));

    for (size_t i = 0; i < NUM_OF_BITES; i++) {
        if (i == NUM_OF_BITES - 15) {
            ptr++;
            continue;
        }
        bitessum += *ptr++;
    }
    return bitessum;
}
