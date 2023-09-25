#ifndef VALUES_STACK
#define VALUES_STACK

typedef int Elem_t;
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
    long long int bite_sum;
    canary_t canary_right;
};

enum Result {
    SUCCESS,
    NULL_POINTER,
    NO_MEMORY,
    INCORRECT_CAPACITY,
    INCORRECT_SIZE,
    OVERFLOW,
    CANARY_FAULT,
    HASH_ERROR,
    ERROR,
    EMPTY
};

struct Hash {
    long long int bite_sum;
};

#endif
