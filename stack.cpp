#include <stdio.h>
#include "stack.h"
#include "stack_values.h"
#include "assert.h"
#include "hash.h"
#include "config.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define dump(stk, error) StackDump(error, (char *)__FILE__, __LINE__, (char *)__func__, stk);

const int SIZESTK = 8;
const int INCREASE = 2;
const int EMPTY_POSITIONS = 3;
const int NUM_OF_ERRORS = 11;
const Elem_t *POISON_PTR = &POISON;
const canary_t CANARY_VALUE_STACK_LEFT = 0xBADBA5EBA11;
const canary_t CANARY_VALUE_STACK_RIGHT = 0xAB0BA;
const canary_t CANARY_VALUE_DATA_LEFT = 0xC01055A1;
const canary_t CANARY_VALUE_DATA_RIGHT = 0xBADFACE;

enum Result StackCtor(Stack *stk, const char *name, const char *file, const int line, const char *func) {

    assert(stk);
    assert(name);
    assert(file);
    assert(func);

    if (!stk)
        return NULL_POINTER;
    int length = sizeof (Elem_t) * SIZESTK + sizeof (canary_t) * 2;
    stk->data = (Elem_t *) calloc (length, sizeof (char));
    if (!stk->data)
        return NO_MEMORY;
    ((canary_t *) stk->data)[0] = CANARY_VALUE_DATA_LEFT;
    stk->data = (Elem_t *) ((canary_t *) stk->data + 1);
    *((canary_t *)(stk->data + SIZESTK)) = CANARY_VALUE_DATA_RIGHT;

    stk->canary_left = CANARY_VALUE_STACK_LEFT;
    for (size_t i = 0; i < SIZESTK; i++)
        stk->data[i] = POISON;
    stk->capacity = SIZESTK;
    stk->size = 0;
    stk->name = name;
    stk->file = file;
    stk->line = line;
    stk->canary_right = CANARY_VALUE_STACK_RIGHT;
    stk->bite_sum = Bitessum(stk);

    return SUCCESS;
}

enum Result StackPush(Stack *stk, Elem_t n, Hash *hsh) {

    assert(stk);
    assert(hsh);

    unsigned int error = StackVerify(stk, hsh);
    if (error != 0) {
        dump(stk, error)
        return ERROR;
    }
    else {
        if (stk->size + 1 >= stk->capacity) {
            stk->data = StackResize(stk, RAISE);
            if (!stk->data)
                return NO_MEMORY;
        }
        stk->data[stk->size++] = n;
        hsh->bite_sum = Bitessum(stk);
        stk->bite_sum = hsh->bite_sum;
        return SUCCESS;
    }
}

enum Result StackPop(Stack *stk, Elem_t *n, Hash *hsh) {

    assert(stk);
    assert(n);
    assert(hsh);

    unsigned int error = StackVerify(stk, hsh);
    if (error != 0) {
        dump(stk, error)
        return ERROR;
    }
    else {
        if (stk->size - 1 >= 0) {
            *n = stk->data[--stk->size];
            stk->data[stk->size] = POISON;
            if (stk->capacity > SIZESTK && stk->capacity - stk->size > SIZESTK + 5) {
                stk->data = StackResize(stk, CUT);
                if (!stk->data)
                    return NO_MEMORY;
            }
            hsh->bite_sum = Bitessum(stk);
            stk->bite_sum = hsh->bite_sum;
        }
        else {
            return EMPTY;
        }
        return SUCCESS;
    }
}

enum Result StackDtor(Stack *stk, Hash *hsh) {

    assert(stk);
    assert(hsh);

    free((canary_t *)stk->data - 1);
    stk->capacity = -1;
    stk->size = -1;
    stk->name = NULL;
    stk->file = NULL;
    stk->line = NULL;
    stk->func = NULL;
    stk->canary_left = -1;
    stk->canary_right = -1;
    stk->bite_sum = -1;
    HashDtor(hsh);
    return SUCCESS;
};

void PrintStack(const Stack *stk, const Hash *hsh) {

    assert(stk);
    assert(hsh);

    unsigned int error = StackVerify(stk, hsh);
    if (error != 0) {
        dump(stk ,error)
    }
    else {
        printf("POISON VALUE = " output_id "\n", POISON);
        for (size_t i = 0; i < stk->capacity; i++)
            printf(output_id " ", stk->data[i]);
        printf("\n");
    }

}

unsigned int StackVerify(const Stack *stk, const Hash *hsh) {

    assert(stk);
    assert(hsh);

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

    numerror *= 2;
    if (stk->canary_left != CANARY_VALUE_STACK_LEFT)
        error |= numerror;

    numerror *= 2;
    if (stk->canary_right != CANARY_VALUE_STACK_RIGHT)
        error |= numerror;

    numerror *= 2;
    if (((canary_t *)(stk->data))[-1] != CANARY_VALUE_DATA_LEFT)
        error |= numerror;

    numerror *= 2;
    if (*((canary_t *)(stk->data + stk->capacity)) != CANARY_VALUE_DATA_RIGHT)
        error |= numerror;

    numerror *= 2;
    if (stk->bite_sum != hsh->bite_sum)
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
        ERR_ (CANARY_FAULT_STACK_LEFT)
        ERR_ (CANARY_FAULT_STACK_RIGHT)
        ERR_ (CANARY_FAULT_DATA_LEFT)
        ERR_ (CANARY_FAULT_DATA_RIGHT)
        ERR_ (HASH_ERROR)
        ERR_ (ERROR)
        ERR_ (EMPTY)

        default: return "???";
        }

    #undef ERR_
    }

void StackDump(unsigned int error, const char *file, const int line, char *func, const Stack *stk) {

    assert(file);
    assert(func);
    assert(stk);

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

        PrintInfo(stk, file, func, line);
    }
}

void PrintInfo(const Stack *stk, const char *file, const char *func, const int line) {

    assert(stk);
    assert(file);
    assert(func);

    int col = 0;

    fprintf(stderr, "Stack \"%s\" [%p] from \"%s\" (%d)\ncalled from \"%s\" (%d)\n", stk->name, stk, stk->file, stk->line, file, line);
    printf("{size = %d\n capacity = %d\n data [%p]\n", stk->size, stk->capacity, stk->data);
    if (stk->capacity > 0 && stk->data) {
        printf("\t{\n");
        for (size_t i = 0; i < stk->capacity && col < EMPTY_POSITIONS; i++) {
            if (compare(stk->data + i, POISON_PTR)) {
                col++;
                printf("\t [%lu] = POISON\n", i);
                continue;
            }
            printf("\t*[%lu] = " output_id "\n", i, stk->data[i]);
        }
        printf("\t}\n");
    }
    printf("}\n");
}

Elem_t *StackResize(Stack *stk, const int is_increase) {

    assert(stk);

    if (is_increase) {
        stk->capacity *= INCREASE;
        Elem_t *data = (Elem_t *) realloc (((canary_t *)stk->data - 1), sizeof (Elem_t) * stk->capacity + 2 * sizeof (canary_t));
        data = (Elem_t *)((canary_t *)data + 1);
        for (size_t i = stk->size; i < stk->capacity; i++) {
            stk->data[i] = POISON;
        }
        *((canary_t *)(data + stk->capacity)) = CANARY_VALUE_DATA_RIGHT;
        return data;
    }
    stk->capacity /= INCREASE;
    Elem_t *data = (Elem_t *) realloc (stk->data, sizeof (Elem_t) * stk->capacity + 2 * sizeof (canary_t));
    data = (Elem_t *)((canary_t *)data + 1);
    for (size_t i = stk->size; i < stk->capacity; i++) {
        stk->data[i] = POISON;
    }
    *((canary_t *)(data + stk->capacity)) = CANARY_VALUE_DATA_RIGHT;
    return data;
}

int compare(const void *frst, const Elem_t *scnd) {

    assert(frst);
    assert(scnd);

    char *a = (char *) frst;
    char *b = (char *) scnd;

    for (size_t i = 0; i < sizeof (Elem_t); i++)
        if (*a++ != *b++)
            return 0;
    return 1;
}
