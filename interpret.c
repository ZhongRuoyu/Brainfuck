#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include "brainfuck.h"

static size_t get_destination(const char *source, size_t in);

void interpret(FILE *file) {
    char *source = read_source(file);
    if (source == NULL) {
        fprintf(stderr, "Error: the number of commands '[' and ']' do not match.\n");
        exit(EXIT_FAILURE);
    }

    // for debugging
    // {
    //     printf("%s\n", source);
    //     size_t n = strlen(source);
    //     for (int i = 0; i < n / 10; ++i) printf("%-2d   .    ", i);
    //     printf("\n");
    // }

    unsigned char a[30000] = {0};
    size_t p = 0;

    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;

    for (size_t i = 0; source[i]; ++i) {
        switch (source[i]) {
            case '>': {
                ++p;
                if (p == 30000) {
                    fprintf(stderr, "Error: incrementing pointer to inaccessible cell.\n");
                    while (s->size) pop(s);
                    free(s);
                    free(source);
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case '<': {
                --p;
                if (p == -1) {
                    fprintf(stderr, "Error: decrementing pointer to inaccessible cell.\n");
                    while (s->size) pop(s);
                    free(s);
                    free(source);
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case '+': {
                ++a[p];
                break;
            }
            case '-': {
                --a[p];
                break;
            }
            case '.': {
                putchar(a[p]);
                break;
            }
            case ',': {
                a[p] = getchar();
                break;
            }
            case '[': {
                if (a[p] == 0) {
                    i = get_destination(source, i);
                } else {
                    push(s, i);
                }
                break;
            }
            case ']': {
                if (a[p] != 0) {
                    i = peek(s);
                } else {
                    pop(s);
                }
                break;
            }
            default: {
                break;
            }
        }
    }

    while (s->size) pop(s);
    free(s);
    free(source);
}

static size_t get_destination(const char *source, size_t in) {
    size_t out = in + 1;
    for (size_t level = 1; source[out] && level != 0; ++out) {
        if (source[out] == '[') {
            ++level;
        } else if (source[out] == ']') {
            --level;
        }
    }
    return --out;
}
