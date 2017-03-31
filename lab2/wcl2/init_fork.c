#include <comp421/yalnix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Source file containing init process code which tests the Fork kernel call.

// Main function which executes the init and fork.
int main(int argc, char **argv) {
    printf("Entering init_fork\n");

    int received_pid;
    int exit_status;
    int exit_pid;

    printf("Forking\n");
    received_pid = Fork();
    printf("Received PID %d\n", received_pid);

    if (received_pid == 0) {

        printf("Forking again\n");
        received_pid = Fork();
        printf("Second level received pid: %d\n", received_pid);

        if (received_pid == 0) {
            char **argvec = malloc(sizeof(char *) * 2);
            argvec[0] = (char *)malloc(sizeof(char) * (strlen("init_exit") + 1));
            strcpy(argvec[0], "init_exit");
            argvec[1] = NULL;
            Exec("init_exit", argvec);
        } else {
            printf("Waiting\n");
            exit_pid = Wait(&exit_status);
            printf("Second level waited and got PID %d with exit status %d\n", exit_pid, exit_status);
            Exit(0);
        }


    } else {
        printf("Waiting\n");
        exit_pid = Wait(&exit_status);
        printf("Waited and got PID %d with exit status %d\n", exit_pid, exit_status);
    }

    Exit(0);
}