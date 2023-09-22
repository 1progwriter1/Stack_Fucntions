#include <stdio.h>
#include "stack.h"
#include "values.h"
#include "assert.h"
#include <stdlib.h>

#define dump(stk, error) unsigned int error = 0; StackDump(StackVerify(stk), (char *)__FILE__, __LINE__, (char *)__func__, stk);

const int SIZESTK = 10;
const int INCREASE = 2;
const int EMPTY_POSITIONS = 3;
const int NUM_OF_ERRORS = 6;
const int POISON = -1e6;


char file[] = "hello";
char func[] = "main.b";

enum Result StackCtor(Stack *stk) {

    if (!stk)
        return NULL_POINTER;
    stk->data = (Elem_t *) calloc (SIZESTK, sizeof (int));
    stk->capacity = SIZESTK;
    stk->size = 0;

    return SUCCESS;
}

enum Result StackPush(Stack *stk, Elem_t n) {

    unsigned int error = StackVerify(stk);
    if (error != 0) {
        dump(stk, error);
        return ERROR;
    }
    else {
        if (stk->size + 1 >= stk->capacity) {
            stk->data = StackResize(stk, RAISE);
            if (!stk->data)
                return NO_MEMORY;
        }
        stk->data[stk->size++] = n;
        return SUCCESS;
    }
}

enum Result StackPop(Stack *stk, Elem_t *n) {

    unsigned int error = StackVerify(stk);
    if (error != 0) {
        printf("<%u>\n", error);
        return NULL_POINTER;
    }
    else {
        if (stk->size - 1 >= 0) {
            *n = stk->data[--stk->size];
            stk->data[stk->size] = NULL;
            if (stk->capacity > SIZESTK && stk->capacity - stk->size > SIZESTK + 5) {
                stk->data = StackResize(stk, CUT);
                if (!stk->data)
                    return NO_MEMORY;
            }
        }
        else {
            return EMPTY;
        }
        return SUCCESS;
    }
}

enum Result StackDtor(Stack *stk) {

    assert(stk);

    free(stk->data);
    stk->capacity = -1;
    stk->size = -1;

    return SUCCESS;
};

void PrintStack(Stack *stk) {

    unsigned int error = StackVerify(stk);
    if (error != 0) {
        dump(stk ,error);
    }
    else {
        for (size_t i = 0; i < stk->capacity; i++)
            printf("%d ", stk->data[i]);
        printf("\n");
    }

}

unsigned int StackVerify(const Stack *stk) {

    unsigned int error = 0;

    int numerror = 2;

    if (!stk) {
        error |= numerror;
        return error;
    }

    numerror *= 2;
    if (!stk->data)
        error |= numerror;

    numerror *= 2;
    if (stk->capacity < 0)
        error |= numerror;

    numerror *= 2;
    if (stk->size < 0)
        error |= numerror;

    numerror *= 2;
    if (stk->size >= stk->capacity)
        error |= numerror;

    return error;
}

const char* StackStrError (enum Result error) {

    #define ERR_(code)  case code: return #code;

    switch (error)
        {
        ERR_ (SUCCESS)
        ERR_ (NULL_POINTER)
        ERR_ (NO_MEMORY)
        ERR_ (INCORRECT_CAPACITY)
        ERR_ (INCORRECT_SIZE)
        ERR_ (OVERFLOW)
        ERR_ (ERROR)
        ERR_ (EMPTY)

        default: return "???";
        }

    #undef ERR_
    }

void StackDump(unsigned int error, char *file, int line, char *func, Stack *stk) {

    if (error != 0) {
        printf("Error codes: ");

        const int NUMBER = 1;

        int err = 0;
        for (int i = 0; i < NUM_OF_ERRORS; i++) {
            if ((error | NUMBER) == error) {
                printf("%s%d (%s)", (err? ", " : ""), i, StackStrError ((enum Result) i));
                err = 1;
            }
           error >>= 1;
        }
        printf("\n");

        printf("Stack [%p] from %s (%d)\n\n", stk, file, line);

        PrintInfo(stk, file, func, line);
    }
}

void PrintInfo(Stack *stk, char *file, const char *func, int line) {

    assert(stk);
    assert(file);
    assert(func);

    int col = 0;

    printf("Stack [%p] from \"%s\" (%d)\ncalled from %s\n", stk, file, line, func);
    printf("{size = %d\n capacity = %d\n data [%p]\n", stk->size, stk->capacity, stk->data);
    if (stk->capacity > 0) {
        printf("\t{\n");
        for (size_t i = 0; i < stk->capacity && col < EMPTY_POSITIONS; i++)
            if (!stk->data[i]) {
                col++;
                printf("\t [%lu] = NULL(POISON)\n", i);
            }
            else {
                printf("\t*[%lu] = %d\n", i, stk->data[i]);
            }
        printf("\t}\n");
    }
    printf("}");
}

Elem_t *StackResize(Stack *stk, const int operation) {

    assert(stk);

    if (operation) {
        stk->capacity *= INCREASE;
        return (Elem_t *) realloc (stk, sizeof (Elem_t) * stk->capacity);
    }
    stk->capacity /= INCREASE;
    return (Elem_t *) realloc (stk, sizeof (Elem_t) * stk->capacity);
}
