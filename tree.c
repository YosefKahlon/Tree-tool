//
// Created by kahlon on 6/14/23.
//
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


int list(const char *name, const struct stat *status, int type);

int main(int argc, char *argv[]) {
    if (argc == 1)
        ftw(".", list, 1);
    else
        ftw(argv[1], list, 1);
    return 0;
}

int list(const char *name, const struct stat *status, int type) {
    if (type == FTW_NS)
        return 0;

    char perms[10];
    snprintf(perms, sizeof(perms), "%o", status->st_mode & 0777);

    if (type == FTW_F)
        printf("%s %s %s %ld\t%s\n", perms, "FILE", "USER:GROUP", (long)status->st_size, name);

    if (type == FTW_D && strcmp(".", name) != 0)
        printf("%s %s %s %ld\t%s/\n", perms, "DIR", "USER:GROUP", (long)status->st_size, name);

    return 0;
}