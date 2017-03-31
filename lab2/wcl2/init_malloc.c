#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Source file containing init code for process which continually mallocs whole pages.

// Main function which executes the init loop.
int main(int argc, char **argv) {

    int *page1;

    if (argc > 1) {
        int i;
        for (i = 0; i < argc; i++) {
            printf("Init got argument %s in position %d\n", argv[i], i);
        }
    }

    while (true) {
        printf("Initializing with PID = %u\n", GetPid());

        printf("Mallocing a page\n");
        page1 = malloc(100 * PAGESIZE);

        if (page1 == NULL) {
            int i;
            for (i = 0; i < 5; i++) {
                Delay(1);
                Pause();
            }

            printf("Couldn't malloc way too much memory\n");
            Exit(-1);
        }

        printf("Delaying for 1 tick\n");
        Delay(1);
        Pause();
    }

    return 0;
}