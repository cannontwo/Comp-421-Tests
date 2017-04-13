#include <stdio.h>
#include <comp421/iolib.h>
#include <comp421/filesystem.h>
#include <comp421/yalnix.h>
#include <string.h>

int main(int argc, char **argv) {

    int i;
    int fd;
    int len;
    char buf1[DIRNAMELEN];
    char buf2[DIRNAMELEN];

    for (i = 1; i < 7; i++) {
        sprintf(buf1, "dir0%d", i);

        printf("Making directory dir0%d\n", i);

        if (MkDir(buf1)) {
            printf("Something went wrong making directory dir0%d\n", i);
            return ERROR;
        }

        printf("Changing to directory dir0%d\n", i);

        if (ChDir(buf1) == ERROR) {
            printf("Something went wrong changing to directory dir0%d\n", i);
            return ERROR;
        }
    }

    if (SymLink("/dir01/dir02", "link1")) {
        printf("Something went wrong making symlink\n");
        return ERROR;
    }

    if (ChDir("/dir01/dir02")) {
        printf("Something went wrong switching to dir02\n");
        return ERROR;
    }

    if ((fd = Create("/dir01/dir02/dir03/dir04/dir05/dir06/link1/a")) == ERROR) {
        printf("Something went wrong creating file a\n");
        return ERROR;
    }

    sprintf(buf2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    printf("Write returned %d\n", Write(fd, buf2, (int)strlen(buf2)));

    if (Create("b") == ERROR) {
        printf("Something went wrong creating file b\n");
        return ERROR;
    }

    if (Link("/dir01/dir02/a", "/dir01/c")) {
        printf("Something went wrong linking c\n");
        return ERROR;
    }

    if (Unlink("/dir01/dir02/dir03/dir04/dir05/dir06/link1/a")) {
        printf("Something went wrong deleting a\n");
        return ERROR;
    }

    if ((fd = Open("/dir01/c")) == ERROR) {
        printf("Something went wrong opening file c\n");
        return ERROR;
    }

    if ((len = Read(fd, buf2, DIRNAMELEN)) == ERROR) {
        printf("Something went wrong reading from c\n");
        return ERROR;
    }

    buf2[len] = '\0';

    printf("Read got %s\n", buf2);

    printf("Done\n");

    return 0;
}
