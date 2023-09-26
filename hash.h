#ifndef HASH_STACK
#define HASH_STACK

#include "stack_values.h"
#include "hash.h"
#include "config.h"

unsigned long long HashCount(const Stack *stk);
enum Result HashCreate(Stack *stk, int id);
void clean();
void HashClean(int id);
int HashCheck(const Stack *stk);

#endif
