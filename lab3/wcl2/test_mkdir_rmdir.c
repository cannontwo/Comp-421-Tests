#include <stdio.h>
#include <comp421/iolib.h>
#include <comp421/filesystem.h>
#include <comp421/yalnix.h>

int main(int argc, char **argv) {

    int i;
    char buf1[DIRNAMELEN];
    char buf2[DIRNAMELEN];

    for (i = 0; i < 10; i++) {
        sprintf(buf1, "%d", i);
        sprintf(buf2, ".");

        printf("Making directory %d\n", i);

        if (MkDir(buf1)) {
            printf("Something went wrong making directory %d\n", i);
            return ERROR;
        }

        printf("Changing to directory %d\n", i);

        if (ChDir(buf1) == ERROR) {
            printf("Something went wrong changing to directory %d\n", i);
            return ERROR;
        }
    }

    for (i = 9; i >= 0; i--) {
        sprintf(buf1, "%d", i);
        sprintf(buf2, "..");

        printf("Changing to parent directory\n");

        if (ChDir(buf2)) {
            printf("Something went wrong changing to parent directory\n");
            return ERROR;
        }

        printf("Removing directory %d\n", i);

        if (RmDir(buf1)) {
            printf("Something went wrong removing directory %i\n", i);
            return ERROR;
        }

    }

    printf("Created all directories\n");

    return 0;
}
