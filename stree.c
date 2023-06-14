//
// Created by kahlon on 6/14/23.
//


/* nftw_dir_tree.c
   Demonstrate the use of nftw(3). Walk though the directory tree specified
   on the command line (or the current working directory if no directory
   is specified on the command line), displaying an indented hierarchy
   of files in the tree. For each file, display:
      * a letter indicating the file type (using the same letters as "ls -l")
      * a string indicating the file type, as supplied by nftw()
      * the file's i-node number.
*/
#define _XOPEN_SOURCE 600 /* Get nftw() */
#include <ftw.h>
#include <sys/types.h>    /* Type definitions used by many programs */
#include <stdio.h>        /* Standard I/O functions */
#include <stdlib.h>       /* Prototypes of commonly used library functions,
                             plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>       /* Prototypes for many system calls */
#include <errno.h>        /* Declares errno and defines error constants */
#include <string.h>       /* Commonly used string-handling functions */

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


/**
 * This function is defined to retrieve the permission
 * string of a file given its mode. It takes the file mode as an argument
 * and returns a string representing the permissions.
 */
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

/**
 * name = The path of the file or directory.
 *
 *
 */

int list(const char *name, const struct stat *status, int type, struct FTW *ftwb) {


    char* perms = get_permissions(status->st_mode);

    // The object is NOT a symbolic link and is one for
    // which stat() could not be executed
    if (type == FTW_NS) {
        return 0;
    }


    for (int i = 0; i < ftwb->level - 1; i++) {
        printf("│   ");
    }

    //The object is a  file directory
    if (type == FTW_F) {

        //returns a struct passwd pointer containing information about the user associated with that user ID.
        struct passwd *user = getpwuid(status->st_uid);

        //returns a struct group pointer containing information about the group associated with that group ID.
        struct group *group = getgrgid(/* group ID of the file or directory*/status->st_gid);

        printf("├── [-%s %10s %10s %8lld]  %s\n",
               perms,
               (user != NULL) ? user->pw_name : "",//user
               (group != NULL) ? group->gr_name : "",//group
               (long long)status->st_size,//size of the file
               &name[ftwb->base]);//name of file

        //The object is a directory
    } else if (type == FTW_D && strcmp(".", name) != 0) {
        struct passwd *user = getpwuid(status->st_uid);
        struct group *group = getgrgid(status->st_gid);
        printf("├── [-%s %10s %10s %8lld]  %s/\n",
               perms,
               (user != NULL) ? user->pw_name : "",
               (group != NULL) ? group->gr_name : "",
               (long long)status->st_size,//size of the file
               &name[ftwb->base]);
    }
    return 0;
}

int main(int argc, char *argv[]) {

    //current working directory
    if (argc == 1)
        ftw(".", (__ftw_func_t)list, 1);

    //different directory.
    else
        ftw(argv[1], (__ftw_func_t)list, 1);
    return 0;
}