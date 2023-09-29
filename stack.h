#ifndef STACK_STACK
#define STACK_STACK

#include "stack_values.h"

enum Result StackCtor(Stack *stk, const char *name, const char *file, const int line, const char *func);
enum Result StackPop(Stack *stk, Elem_t *n);
enum Result StackPush(Stack *stk, Elem_t n);
enum Result StackDtor(Stack *stk);
void PrintStack(const Stack *stk);
void StackDump(unsigned int error, const char *file, const int line, char *func, const Stack *stk);
unsigned int StackVerify(const Stack *stk);
void PrintInfo(const Stack *stk, const char *file, const char *func, const int line);
void StackResize(Stack *stk, const int operation);
const char* StackStrError (enum Result error);
int compare(const void *frst, const Elem_t *scnd);
void Detor();
void fileclose(FILE *fn);
FILE *fileopen(const char *filename);
void Poison_fill(Stack *stk);
static void SetCanary(Stack *stk);

#endif
