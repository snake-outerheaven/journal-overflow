#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;

Stack *init(void);
int kill(Stack *);

int push(Stack *, int *);
int pop(Stack *, int *);

#endif
