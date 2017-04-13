#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Source file containing init process code which tests the Exec kernel call.

// Main function which executes the init loop.
int main(int argc, char **argv) {
    printf("Entering init_exec\n");

    char **argvec = malloc(sizeof(char *) * 3);
    argvec[0] = (char *)malloc(sizeof(char) * (strlen("init") + 1));
    strcpy(argvec[0], "init");
    argvec[1] = (char *)malloc(sizeof(char) * (strlen("whatever") + 1));
    strcpy(argvec[1], "whatever");
    argvec[2] = NULL;

    printf("Executing init\n");
    Exec("init", argvec);

    return 0;
}
