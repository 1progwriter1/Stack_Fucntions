#include <stdio.h>
#include "stack.h"
#include "stack_values.h"
#include "config.h"

/**
 * Stack Functions.
 * Define type of elements, output specifier, POISON value and output file in header-file config.h.
 *
 * Detor() is necessary for memory clean and fileclose is necessary to close the log file
 */

#define info(stk) PrintInfo(&stk, (char *)__FILE__, (char *)__func__, __LINE__);
#define STACK_CTOR(stk) StackCtor(&stk, #stk, (char *)__FILE__, __LINE__, (char *)__func__, &current_id);
int current_id = 0;

int main() {

    Stack stk = {};
    Stack d = {};

    STACK_CTOR(stk)
    STACK_CTOR(d)

    Elem_t n = 0;
    StackPush(&d, 9);
    StackPop(&d, &n);

    info(d)


    for (size_t i = 0; i < 17; i++)
        StackPush(&stk, i);

    info(stk)


    #ifdef log_file
    fileclose(FILE *fn)
    #endif

    Detor();
    return 0;
}
