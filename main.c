#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brainfuck.h"

static void usage(const char *basename, int is_failure);
static const char *get_basename(const char *path);

int main(int argc, char **argv) {
    const char *basename = get_basename(argv[0]);

    if (argc != 2) usage(basename, 1);

    if (strcmp(argv[1], "-h") == 0) {
        usage(basename, 0);
    } else if (strcmp(argv[1], "--help") == 0) {
        usage(basename, 0);
    } else {
        FILE *file;
        if ((file = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: cannot open file.", argv[1]);
            exit(EXIT_FAILURE);
        }
        SourceFile *source = read_source(file);
        fclose(file);
        interpret(source);
    }

    return 0;
}

static void usage(const char *basename, int is_failure) {
    fprintf(is_failure ? stderr : stdout,
            "Usage:\n"
            "    %s <file>\n"
            "    %s {-h|--help}\n"
            "\n"
            "Option:\n"
            "        <file>  Interpret the brainfuck script given.\n"
            "    -h, --help  Display this help message.\n"
            "\n",
            basename, basename);
    exit(is_failure ? EXIT_FAILURE : EXIT_SUCCESS);
}

static const char *get_basename(const char *path) {
    const char *basename = strrchr(path, '/');
    if (basename) return basename + 1;
    basename = strrchr(path, '\\');
    if (basename) return basename + 1;
    return path;
}
