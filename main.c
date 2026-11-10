#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include "indent.h"

#define BRANCH "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 "   // "├── "
#define LAST   "\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 "   // "└── "
#define PIPE   "\xe2\x94\x82   "                         // "│   "


static int skip_dots(const struct dirent *e) {
    return strcmp(e->d_name, ".") != 0 && strcmp(e->d_name, "..") != 0;
}

int dive(int level, const char *path) {
    // print current directory
    const char *last_slash = strrchr(path, '/');
    const char *cur_dir = last_slash ? last_slash + 1 : path;
    print_with_indent(level, cur_dir, 1);
    
    level += 1;

    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror(path);
        return 1;
    }

    struct dirent **list;
    int n = scandir(path, &list, skip_dots, alphasort);

    int count = 1;
    int current = 1;
    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }
        if (entry->d_type == DT_DIR) {
            char child[PATH_MAX];
            snprintf(child, sizeof(child), "%s/%s", path, name);
            dive(level, child);
        } else {
            if (current == n) {
                print_with_indent(level, name, 1);
            } else {
                print_with_indent(level, name, 0);
            }
        }

        current += 1;
    }

    closedir(dir);
    return 0;
}

int walk(const char *path, char *indentations) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to read directory");
        return 1;
    }

    struct dirent **list;
    int n = scandir(path, &list, skip_dots, alphasort);

    int level = 0;
    int current = 1;
    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }
        if (entry->d_type == DT_DIR) {
            char child[PATH_MAX];
            snprintf(child, sizeof(child), "%s/%s", path, name);
            dive(level, child);
        } else {
            if (current == n) {
                print_with_indent(level, name, 1);
            } else {
                print_with_indent(level, name, 0);
            }
        }

        current += 1;
    }
    
    closedir(dir);
    return 0;
}

int main(int argc, char **argv) {
    const char *path = "."; // default current path
    
    if (argc > 1) {
        path = argv[1];
    }

    
    printf("Path: %s \n", path);
    
    char *indentations = LAST;
    int err = walk(path, indentations);
    return err;
}