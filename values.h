#ifndef VALUES_STACK
#define VALUES_STACK

typedef int Elem_t;

const int RAISE = 1;
const int CUT = 0;

struct Stack {
    Elem_t *data;
    Elem_t size;
    Elem_t capacity;
    char *file;
    int line;
};

enum Result {
    SUCCESS,
    NULL_POINTER,
    NO_MEMORY,
    INCORRECT_CAPACITY,
    INCORRECT_SIZE,
    OVERFLOW,
    ERROR,
    EMPTY
};
#endif
