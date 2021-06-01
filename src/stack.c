#include <stdlib.h>

#include "brainfuck.h"

void push(Stack *s, size_t line, size_t column) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->val.line = line;
    node->val.column = column;
    node->next = s->top;
    s->top = node;
    ++s->size;
}

void pop(Stack *s) {
    if (s->top) {
        StackNode *p = s->top;
        s->top = s->top->next;
        --s->size;
        free(p);
    }
}

FilePosition peek(const Stack *s) {
    return s->top->val;
}
