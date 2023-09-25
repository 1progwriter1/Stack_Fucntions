#include <stdio.h>
#include "stack.h"
#include "stack_values.h"
#include "assert.h"
#include "hash.h"
#include <stdlib.h>

#define dump(stk, error) StackDump(error, (char *)__FILE__, __LINE__, (char *)__func__, stk);

const int SIZESTK = 10;
const int INCREASE = 2;
const int EMPTY_POSITIONS = 3;
const int NUM_OF_ERRORS = 8;
const int POISON = -1e6;
const canary_t CANARY_VALUE_STACK = 0xBADBA5EBA11;
const canary_t CANARY_VALUE_DATA = 0xC01055A1;

enum Result StackCtor(Stack *stk, const char *name, const char *file, const int line, const char *func) {

    assert(stk);
    assert(name);
    assert(file);
    assert(func);

    if (!stk)
        return NULL_POINTER;
    int length = sizeof (Elem_t) * SIZESTK + sizeof (canary_t) * 2;
    stk->data = (Elem_t *) calloc (length, sizeof (char));
    ((canary_t *) stk->data)[0] = CANARY_VALUE_DATA;
    stk->data = stk->data + sizeof (canary_t) / sizeof (Elem_t);
    *((canary_t *)(stk->data + 10)) = CANARY_VALUE_DATA;
    if (!stk->data)
        return NO_MEMORY;

    stk->canary_left = CANARY_VALUE_STACK;
    for (size_t i = 0; i < SIZESTK; i++)
        stk->data[i] = POISON;
    stk->capacity = SIZESTK;
    stk->size = 0;
    stk->name = name;
    stk->file = file;
    stk->line = line;
    stk->canary_right = CANARY_VALUE_STACK;
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

    free(stk->data - sizeof (canary_t) / sizeof (Elem_t));
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
        for (size_t i = 0; i < stk->capacity; i++)
            if (stk->data[i] != POISON)
                printf("%d ", stk->data[i]);
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
    if (stk->canary_left != CANARY_VALUE_STACK | stk->canary_right != CANARY_VALUE_STACK | ((canary_t *) stk->data)[-1] != CANARY_VALUE_DATA | *((canary_t *) (stk->data + stk->capacity)) != CANARY_VALUE_DATA)
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
        ERR_ (CANARY_FAULT)
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
        for (size_t i = 0; i < stk->capacity && col < EMPTY_POSITIONS; i++)
            if (stk->data[i] == POISON) {
                col++;
                printf("\t [%lu] = POISON\n", i);
            }
            else {
                printf("\t*[%lu] = %d\n", i, stk->data[i]);
            }
        printf("\t}\n");
    }
    printf("}\n");
}

Elem_t *StackResize(Stack *stk, const int operation) {

    assert(stk);

    if (operation) {
        stk->capacity *= INCREASE;
        Elem_t *data = (Elem_t *) realloc (stk, sizeof (Elem_t) * stk->capacity + 2 * sizeof (canary_t));
        data += sizeof (canary_t) / sizeof (Elem_t);
        for (size_t i = stk->size; i < stk->capacity; i++) {
            stk->data[i] = POISON;
        }
        *((canary_t *)(data + stk->capacity)) = CANARY_VALUE_DATA;
        return data;
    }
    stk->capacity /= INCREASE;
    Elem_t *data = (Elem_t *) realloc (stk, sizeof (Elem_t) * stk->capacity + 2 * sizeof (canary_t));
    data += sizeof (canary_t) / sizeof (Elem_t);
    for (size_t i = stk->size; i < stk->capacity; i++) {
        stk->data[i] = POISON;
    }
    *((canary_t *)(data + stk->capacity)) = CANARY_VALUE_DATA;
    return data;
}
