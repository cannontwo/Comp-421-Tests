#include <stdio.h>
#include <comp421/iolib.h>

int main(int argc, char **argv) {

    int err;

    if (MkDir("dir")) {
        printf("Something went wrong creating directory\n");
    }

    if (SymLink("dir/a", "b")) {
        printf("Something went wrong creating SymLink b\n");
    }

    if (SymLink("/b", "dir/a")) {
        printf("Something went wrong creating SymLink a\n");
    }

    // Should fail due to excessive symlink expansion
    err = ChDir("b");

    printf("ChDir returned %d\n", err);

    return 0;
}
