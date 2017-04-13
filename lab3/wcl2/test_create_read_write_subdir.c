
#include <stdio.h>
#include <comp421/iolib.h>
#include <comp421/filesystem.h>
#include <comp421/yalnix.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv) {

    int fd;
    int i;
    char buf[DIRNAMELEN];
    char tmp[DIRNAMELEN];
    struct Stat statbuf;

    sprintf(tmp, ".");

    if (MkDir("dir")) {
        printf("Something went wrong while making a directory\n");
    }

    for (i = 0; i < 10; i++) {
        sprintf(buf, "/dir/%d", i);

        printf("Creating file /dir/%d\n", i);
        fd = Create(buf);

        Stat(tmp, &statbuf);
        ChDir("dir");
        ChDir("..");

        if (fd == ERROR) {
            printf("Something went wrong creating file /dir/%d\n", i);
            return ERROR;
        } else {
            strncpy(buf, "Hello world", DIRNAMELEN);
            printf("Writing to file /dir/%d\n", i);
            if (Write(fd, buf, (int)strlen(buf)) != strlen(buf)) {
                printf("Unable to write to file /dir/%d\n", i);
                return ERROR;
            }

            if (Seek(fd, 0, SEEK_SET)) {
                printf("Unable to seek to the beginning of file /dir/%d\n", i);
                return ERROR;
            }

            if (Read(fd, buf, (int)strlen(buf)) != strlen(buf)) {
                printf("Unable to read back from file /dir/%d\n", i);
                return ERROR;
            }
            printf("Read '%s' from file /dir/%d\n", buf, i);
        }
    }

    printf("Wrote to all files\n");

    return 0;
}
