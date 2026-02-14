#include <stddef.h>

typedef struct stack Stack;

Stack *stack_init(void);
int stack_kill(Stack **);

int peek(const Stack *, int *);
size_t get_size(const Stack *);

int push(Stack *, int *);
int pop(Stack *, int *);

int stack_print(const Stack *);
int stack_to_array(const Stack *, int *);
