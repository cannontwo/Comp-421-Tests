#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Source file containing init process code which writes repeatedly to a terminal.

// Main function which executes the init loop.
int main(int argc, char **argv) {

    char buf[TERMINAL_MAX_LINE];
    int i = 0;

    if (argc > 0) {
        int j;
        for (j = 0; j < argc; j++) {
            printf("Init got argument %s in position %d\n", argv[j], j);
        }

        strcpy(buf, argv[1]);
    } else {
        strcpy(buf, "foobar\n");
    }

    while (true) {
        printf("Writing to terminal %d", i);
        TtyWrite(i, buf, strlen(buf) + 1);
        Pause();

        i = (i + 1) % 4;
    }

    return 0;
}