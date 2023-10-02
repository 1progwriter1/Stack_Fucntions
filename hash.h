#ifndef HASH_STACK
#define HASH_STACK

#include "stack_values.h"
#include "hash.h"

/**
 * Function calculate hash using djb2 algorithm from // algorithm from https://github.com/dim13/djb2/blob/master/docs/hash.md?ysclid=ln4xxrs0cd483255939
 *
 * @param stk Stack for which hash is creating
 *
 * @return value of hash
 */
unsigned long long HashCount(const Stack *stk);
enum Result HashCreate(Stack *stk);
void clean();
void HashClean(int id);
int HashCheck(const Stack *stk);

#endif
