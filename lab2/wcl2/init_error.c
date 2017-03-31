#include <comp421/hardware.h>
#include <comp421/yalnix.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Source file containing erroring init code to test traps.

// Main function which executes tests.
int main(int argc, char **argv) {

    int i = 1 / 0;

    return 0;
}