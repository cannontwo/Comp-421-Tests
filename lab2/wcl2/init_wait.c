#include <comp421/yalnix.h>
#include <stdio.h>

// Source file containing init process code which tests the Wait kernel call.

// Main function which executes the init loop.
int main(int argc, char **argv) {
    printf("Entering init_wait\n");

    int exit_status, exited_pid;

    printf("Waiting\n");
    exited_pid = Wait(&exit_status);
    printf("Got exited PID %d with status %d\n", exited_pid, exit_status);

    return exited_pid;
}