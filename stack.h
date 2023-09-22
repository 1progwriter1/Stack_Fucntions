#ifndef STACK_STACK
#define STACK_STACK

#include "values.h"

enum Result StackCtor(Stack *stk);
enum Result StackPop(Stack *stk, Elem_t *n);
enum Result StackPush(Stack *stk, Elem_t n);
enum Result StackDtor(Stack *stk);
void PrintStack(Stack *stk);
void StackDump(unsigned int error, char *file, int line, char *func, Stack *stk);
unsigned int StackVerify(const Stack *stk);
void PrintInfo(Stack *stk, char *file, const char *func, int line);
Elem_t *StackResize(Stack *stk, const int operation);
const char* StackStrError (enum Result error);

#endif
