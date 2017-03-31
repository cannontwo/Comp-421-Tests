#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Source file containing init process code which writes repeatedly to a terminal.

// Main function which executes the init loop.
int main(int argc, char **argv) {

    int pid;
    char buf[TERMINAL_MAX_LINE];
    int i = 0;

    while (true) {
        pid = Fork();

        if (pid == -1) {
            break;
        }

        sprintf(buf, "Hello number %d from process %d\n", i / 4, GetPid());

        printf("Writing to terminal %d from PID %d\n", i % 4, GetPid());
        TtyWrite(i % 4, buf, strlen(buf) + 1);

        i++;
    }

    return 0;
}