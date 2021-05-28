#include <stdio.h>
#include <stdlib.h>

#include "brainfuck.h"

void error(SourceFile *source, size_t line, size_t column, const char *msg) {
    fprintf(stderr, "\n");
    fprintf(stderr, "At Line %d, Column %d: error: %s\n", line + 1, column + 1, msg);
    fprintf(stderr, "    %s\n", source->lines[line]);
    fprintf(stderr, "    %*s^\n", column, "");
    fprintf(stderr, "\n");
}

void cleanup_source(SourceFile *source) {
    for (size_t i = 0; i < source->line_count; ++i) {
        free(source->lines[i]);
    }
    free(source->lines);
    free(source);
}

void cleanup_stack(Stack *s) {
    while (s->size) pop(s);
    free(s);
}
