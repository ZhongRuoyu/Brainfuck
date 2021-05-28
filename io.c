#include <stdio.h>
#include <stdlib.h>

#include "brainfuck.h"

char *read_source(FILE *file) {
    unsigned buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    unsigned char_count = 0;

    int loop_level = 0;

    for (char ch; (ch = getc(file)) != EOF;) {
        switch (ch) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']': {
                break;
            }
            default: {
                continue;
            }
        }
        if (char_count == buffer_size) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
        }
        buffer[char_count++] = ch;
        if (ch == '[') {
            ++loop_level;
        } else if (ch == ']') {
            --loop_level;
            if (loop_level < 0) {
                free(buffer);
                return NULL;
            }
        }
    }

    if (loop_level != 0) {
        free(buffer);
        return NULL;
    }

    buffer[char_count] = '\0';
    buffer = (char *)realloc(buffer, (char_count + 1) * sizeof(char));
    return buffer;
}
