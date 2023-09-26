#include <stdio.h>
#include "stack.h"
#include "stack_values.h"
#include "config.h"
/**
 * Stack Functions.
 * Define type of elements, output specifier and POISON value in header-file config.h.
 *
 * Detor() is necessary for memory clean
 */
#define info(stk) PrintInfo(&stk, (char *)__FILE__, (char *)__func__, __LINE__);
#define STACK_CTOR(stk, id) StackCtor(&stk, #stk, (char *)__FILE__, __LINE__, (char *)__func__, &id);
int current_id = 0;

int main() {

    Detor();

    return 0;
}
