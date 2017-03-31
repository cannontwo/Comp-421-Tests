#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdbool.h>
#include <stdio.h>
#include <memory.h>

// Source file containing init process code with a large stack which checks stack page validity.

int arr_len = PAGESIZE / sizeof(int);

// Helper function to print an integer array.
void print_array(int len, int foo[]) {
    int i;

    printf("Table of length %d:\n", len);

    for (i = 0; i < len; i++) {
        printf("%d ", foo[i]);
    }

    printf("\n");
}

// Function which does simple recursion to expand stack indefinitely
void recursive_func(int foo, int bar[]) {
    printf("Recursing\n");

    if (foo > arr_len / 2) {
        return;
    }

    int baz[arr_len];
    memcpy(baz, bar, sizeof(int) * arr_len);

    baz[foo] = 1;
    baz[arr_len - foo] = 1;

    print_array(arr_len, baz);

    Pause();
    recursive_func(foo + 1, baz);
}

// Main function which executes the init loop.
int main(int argc, char **argv) {

    int bar[PAGESIZE];

    // Call recursive func to repeatedly expand stack.
    recursive_func(0, bar);

    return 0;
}