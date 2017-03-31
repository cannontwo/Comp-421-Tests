#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Source file containing infinite forking init process code.

// Main function which executes the init loop.
int main(int argc, char **argv) {

    int received_pid;
    int exit_status;
    int exit_pid;

    int *page;

//    printf("Forking Infinitely\n");
    received_pid = Fork();
    printf("Received PID %d\n", received_pid);

    if (received_pid == 0) {

        page = malloc(10 * PAGESIZE);

        if (page == NULL) {
            printf("Couldn't allocate memory\n");
            Exit(-1);
        }

        page[100] = 1;

        // Delay for display purposes
        Delay(1);
        Pause();

        char **argvec = malloc(sizeof(char *) * 2);
        argvec[0] = (char *)malloc(sizeof(char) * (strlen(argv[0]) + 1));
        strcpy(argvec[0], argv[0]);
        argvec[1] = NULL;

        Exec(argv[0], argvec);
    } else if (received_pid > 0){
        char buf[TERMINAL_MAX_LINE];

        sprintf(buf, "foobar from parent of process %d\n", received_pid);

        TtyWrite(0, buf, strlen(buf) + 1);
        printf("Waiting\n");
        exit_pid = Wait(&exit_status);
        printf("Waited and got PID %d with exit status %d\n", exit_pid, exit_status);
    } else {
        printf("Something went wrong while forking\n");
        Exit(-1);
    }

    return 0;
}
