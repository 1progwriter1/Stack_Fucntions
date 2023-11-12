#ifndef STACK_STACK
#define STACK_STACK

#include "stack_values.h"

int StackCtor(Stack *stk, const char *name, const char *file, const int line, const char *func);
int StackPop(Stack *stk, Elem_t *n);
int StackPush(Stack *stk, Elem_t n);
int StackDtor(Stack *stk);
void PrintStack(const Stack *stk);
void Detor();
void closefile(FILE *fn);
FILE *fileopen(const char *filename);

#endif
