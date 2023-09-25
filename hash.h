#ifndef HASH_STACK
#define HASH_STACK

#include "stack_values.h"
#include "hash.h"

enum Result HashCtor(Hash *hsh, Stack *stk);
long long int Bitessum(Stack *stk);
enum Result HashDtor(Hash *hsh);

#endif
