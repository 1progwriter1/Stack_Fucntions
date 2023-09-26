#include <stdio.h>
#include "stack.h"
#include "hash.h"
#include "stack_values.h"
#include "config.h"

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

    Elem_t n = 0;
    StackPush(&stk, 27, &hsh1);
    StackPush(&stk, 11, &hsh1);
    printf("%d " output_id "\n", StackPop(&stk, &n, &hsh1), n);

    badstk.data[-1] = 1;
    badstk.bite_sum = 9;

    PrintStack(&badstk, &hsh2);

    printf("\n\n");

    StackPush(&stk, 'd', &hsh1);

    info(stk);

    return 0;
}
