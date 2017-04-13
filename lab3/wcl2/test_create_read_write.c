// Simple test program

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

    for (i = 0; i < 10; i++) {
        sprintf(buf, "%d", i);

        printf("Creating file %d\n", i);
        fd = Create(buf);

        Stat(tmp, &statbuf);

        if (fd == ERROR) {
            printf("Something went wrong creating file %d\n", i);
            return ERROR;
        } else {
            strncpy(buf, "Hello world", DIRNAMELEN);
            printf("Writing to file %d\n", i);
            if (Write(fd, buf, (int)strlen(buf)) != strlen(buf)) {
                printf("Unable to write to file %d\n", i);
                return ERROR;
            }

            if (Seek(fd, 0, SEEK_SET)) {
                printf("Unable to seek to the beginning of file %d\n", i);
                return ERROR;
            }

            if (Read(fd, buf, (int)strlen(buf)) != strlen(buf)) {
                printf("Unable to read back from file %d\n", i);
                return ERROR;
            }
            printf("Read '%s' from file %d\n", buf, i);
        }
    }

    printf("Wrote to all files\n");

    return 0;
}
