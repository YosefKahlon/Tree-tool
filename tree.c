//
// Created by kahlon on 6/14/23.
//
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
int directory_count = 0;
int file_count = 0;
typedef int (*ftw_func_t)(const char *, const struct stat *, int, struct FTW *);

struct FTW {
    int base;
    int level;
};

char* get_permissions(mode_t mode) {
    static char perms[10];
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';
    return perms;
}

int list(const char *name, const struct stat *status, int type, struct FTW *ftwbuf) {


    if (type == FTW_NS)
        return 0;

    char* perms = get_permissions(status->st_mode);

    for (int i = 0; i < ftwbuf->level - 1; i++)
        printf("%s", "├── [   ");

    if (ftwbuf->level > 0)
        printf("%s", "├── -");

    if (type == FTW_F) {
        file_count++;


        struct passwd *pw = getpwuid(status->st_uid);
        struct group *gr = getgrgid(status->st_gid);
        printf("%s  %-8s %-8s %8lld] %s\n", perms, pw->pw_name, gr->gr_name, (long long)status->st_size, &name[ftwbuf->base]);
    }

    if (type == FTW_D && ftwbuf->level > 0) {
        directory_count++;
        printf("%s  %-8s %-8s %8lld] %s/\n", perms, "", "", (long long) status->st_size, &name[ftwbuf->base]);
    }
    return 0;
}

int main(int argc, char *argv[]) {


    if (argc == 1)
        ftw(".", (ftw_func_t)list, 20);
    else
        ftw(argv[1], (ftw_func_t)list, 20);

    printf("%d directories, %d files\n", directory_count, file_count);

    return 0;
}
