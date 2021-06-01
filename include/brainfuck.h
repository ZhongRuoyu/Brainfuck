#ifndef BRAINFUCK_H_
#define BRAINFUCK_H_

#include <stdio.h>

typedef struct SourceFile {
    size_t line_count;
    char **lines;
} SourceFile;

typedef struct FilePosition {
    size_t line;
    size_t column;
} FilePosition;

typedef struct StackNode {
    FilePosition val;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    size_t size;
} Stack;

// error.c begin

void error(const SourceFile *source, size_t line, size_t column, const char *msg);
void cleanup_source(SourceFile *source);
void cleanup_stack(Stack *s);

// end error.c

// interpret.c begin

void interpret(SourceFile *source);

// end interpret.c

// io.c begin

SourceFile *read_source(FILE *file);

// end io.c

// stack.c begin

void push(Stack *s, size_t line, size_t column);
void pop(Stack *s);
FilePosition peek(const Stack *s);

// end stack.c

#endif  // BRAINFUCK_H_
