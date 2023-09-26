#ifndef VALUES_STACK
#define VALUES_STACK

#include "config.h"

typedef unsigned long long canary_t;

const int RAISE = 1;
const int CUT = 0;

struct Stack {
    canary_t canary_left;
    Elem_t *data;
    Elem_t size;
    Elem_t capacity;
    const char *name;
    const char *file;
    int line;
    const char *func;
    int id;
    canary_t canary_right;
};

enum Result {
    SUCCESS,
    NULL_POINTER,
    NO_MEMORY,
    INCORRECT_CAPACITY,
    INCORRECT_SIZE,
    OVERFLOW,
    CANARY_FAULT_STACK_LEFT,
    CANARY_FAULT_STACK_RIGHT,
    CANARY_FAULT_DATA_LEFT,
    CANARY_FAULT_DATA_RIGHT,
    HASH_ERROR,
    ERROR,
    EMPTY
};

#endif
