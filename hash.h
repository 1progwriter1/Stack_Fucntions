#ifndef HASH_STACK
#define HASH_STACK

#include "stack_values.h"
#include "hash.h"
#include "config.h"


struct Hash {
    unsigned long long bite_sum;
};

enum Result HashCtor(Hash *hsh, Stack *stk);
unsigned long long Bitessum(Stack *stk);
enum Result HashDtor(Hash *hsh);

#endif
