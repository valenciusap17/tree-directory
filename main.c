#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

int dive(int *level, const char *path) {
    *level += 1;
    const char *last_slash = strchr(path, "/");
    const char *cur_dir = last_slash ? last_slash + 1 : path;
    print_with_indent(*level, cur_dir);

    // while ((entry = readdir(dir)) != NULL) {
    //     if (entry->d_type == DT_DIR) {
            
    //     }
    //     printf("%s\n", entry->d_name);
    // }
}

int walk(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to read directory");
        return 1;
    }

    int *level = 0;
    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            char child[PATH_MAX];
            snprintf(child, sizeof(child), "%s/%s", path, *name);
            dive(level, child);
        } else {
            print_with_indent(level, *name);
        }
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