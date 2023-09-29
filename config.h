#ifndef CONFIG_STACK
#define CONFIG_STACK

typedef int Elem_t;

#define output_id "%d"

const Elem_t POISON = -1e6;
// #define logs_file "your_file" -- an example of file define
#define logs_file "logs.txt"
// #define PROTECT // protection activation

#endif
