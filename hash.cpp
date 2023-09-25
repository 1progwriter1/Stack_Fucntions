#include <stdio.h>
#include "hash.h"
#include "stack_values.h"

enum Result HashCtor(Hash *hsh, Stack *stk) {

    hsh->bite_sum = Bitessum(stk);
    return SUCCESS;
}

enum Result HashDtor(Hash *hsh) {

    hsh->bite_sum = -1;
    return SUCCESS;
}

long long int Bitessum(Stack *stk) {

    long long int bitessum = 0;
    const int NUM_OF_BITES = stk->capacity * sizeof (Elem_t) + 2 * sizeof (canary_t);
    char *ptr = (char *)(stk->data - sizeof (canary_t) / sizeof (Elem_t));

    for (size_t i = 0; i < NUM_OF_BITES; i++) {
        bitessum += *ptr++;
    }
    return bitessum;
}
