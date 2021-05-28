#include <stdlib.h>

#include "brainfuck.h"

void push(Stack *s, size_t val) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->val = val;
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

size_t peek(const Stack *s) {
    if (s->top) return s->top->val;
    return 0;
}
