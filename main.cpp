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


int main() {

    Stack stk;
    STACK_CTOR(stk);

    printf("%d", n);

    PrintStack(&stk);

    #ifdef log_file
    fileclose(FILE *fn)
    #endif

    Detor();
    return 0;
}
