#ifndef BRAINFUCK_H_
#define BRAINFUCK_H_

#include <stdio.h>

// interpret.c begin

void interpret(FILE *file);

// end interpret.c

// io.c begin

char *read_source(FILE *file);

// end io.c

// stack.c begin

typedef struct StackNode {
    size_t val;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    size_t size;
} Stack;

void push(Stack *s, size_t val);
void pop(Stack *s);
size_t peek(const Stack *s);

// end stack.c

#endif  // BRAINFUCK_H_
