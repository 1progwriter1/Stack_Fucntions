#include <stdio.h>
#include "stack.h"
#include "values.h"

#define info(stk) PrintInfo(&stk, (char *)__FILE__, (char *)__func__, __LINE__);

int main() {

    Stack stk = {NULL, 0, 0, (char *)__FILE__, __LINE__};
    Stack badstk = {NULL, 0, 0,(char *)__FILE__, __LINE__};
    StackCtor(&stk);
    StackCtor(&badstk);
    Elem_t n = NULL;
    /* PrintStack(&stk);
    StackPush(&stk, 24);
    PrintStack(&stk);
    printf("%d %d\n", StackPop(&stk, &n), n);
    PrintStack(&stk); */

    badstk.data = NULL;
    badstk.capacity = 10;
    badstk.size = -1;

    PrintStack(&badstk);

    printf("\n\n");

    StackPush(&stk, 7);

    info(stk);

    return 0;
}
