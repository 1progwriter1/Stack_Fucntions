#include <stdio.h>
#include "stack.h"
#include "hash.h"
#include "stack_values.h"

#define info(stk) PrintInfo(&stk, (char *)__FILE__, (char *)__func__, __LINE__);
#define STACK_CTOR(stk) StackCtor(&stk, #stk, (char *)__FILE__, __LINE__, (char *)__func__);

int main() {

    Stack stk = {};
    Stack badstk = {};
    STACK_CTOR(stk)
    STACK_CTOR(badstk)
    Hash hsh1 = {};
    Hash hsh2 = {};
    HashCtor(&hsh1, &stk);
    HashCtor(&hsh2, &badstk);
    /* PrintStack(&stk);
    StackPush(&stk, 24);
    PrintStack(&stk);
    printf("%d %d\n", StackPop(&stk, &n), n);
    PrintStack(&stk); */

    badstk.data[-1] = 1;

    PrintStack(&badstk, &hsh2);

    printf("\n\n");

    StackPush(&stk, 7, &hsh1);

    info(stk);

    return 0;
}
