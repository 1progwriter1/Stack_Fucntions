#include <stdio.h>
#include "stack.h"
#include "stack_values.h"
#include "config.h"
#include <stdlib.h>
#include <assert.h>

/**
 * Stack Functions.
 * Define type of elements, output specifier, POISON value and output file in header-file config.h.
 * You also can activate or deactivate protection in header-file config.h.
 *
 * Detor() is necessary for memory clean and fileclose is necessary to close the log file
 */

#define info(stk) PrintInfo(&stk, (char *)__FILE__, (char *)__func__, __LINE__);
#define STACK_CTOR(stk) StackCtor(&stk, #stk, (char *)__FILE__, __LINE__, (char *)__func__);

int main() {

    #ifdef log_file
    fileclose(FILE *fn)
    #endif

    Detor();
    return 0;
}
