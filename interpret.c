#include <stdio.h>
#include <stdlib.h>

#include "brainfuck.h"

static FilePosition get_destination(const SourceFile *source, size_t line, size_t column);

void interpret(SourceFile *source) {
    unsigned char a[30000] = {0};
    size_t p = 0;

    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;

    for (size_t i = 0; i < source->line_count; ++i) {
        for (size_t j = 0; source->lines[i][j] != '\0'; ++j) {
            switch (source->lines[i][j]) {
                case '>':
                    ++p;
                    if (p == 30000) {
                        error(source, i, j, "incrementing pointer to inaccessible cell.");
                        cleanup_stack(s);
                        cleanup_source(source);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '<':
                    --p;
                    if (p == -1) {
                        error(source, i, j, "decrementing pointer to inaccessible cell.");
                        cleanup_stack(s);
                        cleanup_source(source);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '+':
                    ++a[p];
                    break;
                case '-':
                    --a[p];
                    break;
                case '.':
                    putchar(a[p]);
                    break;
                case ',':
                    a[p] = getchar();
                    break;
                case '[':
                    if (a[p] == 0) {
                        FilePosition dest = get_destination(source, i, j);
                        if (dest.line == source->line_count) {
                            error(source, i, j, "could not find matching instruction ']'.");
                            cleanup_stack(s);
                            cleanup_source(source);
                            exit(EXIT_FAILURE);
                        }
                        i = dest.line, j = dest.column;
                    } else {
                        push(s, i, j);
                    }
                    break;
                case ']':
                    if (s->size == 0) {
                        error(source, i, j, "could not find matching instruction '['.");
                        cleanup_stack(s);
                        cleanup_source(source);
                        exit(EXIT_FAILURE);
                    }
                    if (a[p] != 0) {
                        FilePosition dest = peek(s);
                        i = dest.line, j = dest.column;
                    } else {
                        pop(s);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (s->size != 0) {
        FilePosition top = peek(s);
        error(source, top.line, top.column, "unexpected end-of-file -- could not find matching instruction ']'.");
        cleanup_stack(s);
        cleanup_source(source);
        exit(EXIT_FAILURE);
    }

    cleanup_stack(s);
}

static FilePosition get_destination(const SourceFile *source, size_t line, size_t column) {
    if (source->lines[line][++column] == '\0') {
        ++line, column = 0;
    }

    for (size_t level = 1; level != 0 && line < source->line_count;) {
        if (source->lines[line][column] == '[') {
            ++level;
        } else if (source->lines[line][column] == ']') {
            --level;
        }

        if (source->lines[line][++column] == '\0') {
            ++line, column = 0;
        }
    }

    return (FilePosition){.line = line, .column = --column};
}
