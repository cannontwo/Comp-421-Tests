#include <comp421/yalnix.h>
#include <stdio.h>

// Source file containing init process code which tests the Exec kernel call.

// Main function which executes the init loop.
int main(int argc, char **argv) {
    printf("Entering init_exit\n");

    printf("Exiting\n");
    Exit(0);
}
