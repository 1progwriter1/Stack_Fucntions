#ifndef STACK_STACK
#define STACK_STACK

#include "stack_values.h"

enum Result StackCtor(Stack *stk, const char *name, const char *file, const int line, const char *func);
enum Result StackPop(Stack *stk, Elem_t *n, Hash *hsh);
enum Result StackPush(Stack *stk, Elem_t n, Hash *hsh);
enum Result StackDtor(Stack *stk, Hash *hsh);
void PrintStack(const Stack *stk, const Hash *hsh);
void StackDump(unsigned int error, const char *file, const int line, char *func, const Stack *stk);
unsigned int StackVerify(const Stack *stk, const Hash *hsh);
void PrintInfo(const Stack *stk, const char *file, const char *func, const int line);
Elem_t *StackResize(Stack *stk, const int operation);
const char* StackStrError (enum Result error);

#endif
