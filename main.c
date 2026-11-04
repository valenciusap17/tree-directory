#include <stdio.h>
#include <dirent.h>

int walk(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to read directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
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
    
    int err = walk(path);
    return err;
}

int print_with_indent(int level, char *text) {
    if (level < 0) {
        printf("Identation level error: %d", level);
        return 1;
    }

    int spaces = level * 4;
    printf("%*s%s\n", spaces, "", text);
    return 0;
}