#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "indent.h"

#define BRANCH      "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 "     // "├── "
#define LAST        "\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 "     // "└── "
#define PIPE        "\xe2\x94\x82   "                           // "│   "
#define TREE_BLANK  "    "                                      // "    "

int print_with_indent(int level, const char *text, int last) {
    if (level < 0) {
        printf("Identation level error: %d", level);
        return 1;
    }

    if (level == 0) {
        int spaces = level * 4;
        printf("%*s%s%s\n", spaces, "", BRANCH, text);
        return 0;
    }
    if (last == 1) {
        int spaces = (level-1) * 4;
        printf("%s%*s%s%s\n", PIPE, spaces, "", LAST, text);
        return 0;
    }

    int spaces = (level-1) * 4;
    printf("%s%*s%s%s\n", PIPE, spaces, "", BRANCH, text);
    return 0;
}