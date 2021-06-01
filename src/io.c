#include <stdio.h>
#include <stdlib.h>

#include "brainfuck.h"

static char *read_line(FILE *file);

SourceFile *read_source(FILE *file) {
    size_t buffer_size = 128;

    SourceFile *source = (SourceFile *)malloc(sizeof(SourceFile));
    source->line_count = 0;
    source->lines = malloc(buffer_size * sizeof(char *));

    while (!feof(file)) {
        if (source->line_count == buffer_size) {
            buffer_size *= 2;
            source->lines = (char **)realloc(source->lines, buffer_size * sizeof(char *));
        }
        source->lines[source->line_count++] = read_line(file);
    }

    source->lines = (char **)realloc(source->lines, source->line_count * sizeof(char *));
    return source;
}

static char *read_line(FILE *file) {
    size_t buffer_size = 128;

    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    size_t char_count = 0;

    for (char ch; ch = getc(file), ch != '\n' && ch != EOF;) {
        if (char_count == buffer_size) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
        }
        buffer[char_count++] = ch;
    }
    buffer[char_count] = '\0';

    buffer = (char *)realloc(buffer, (char_count + 1) * sizeof(char));
    return buffer;
}
