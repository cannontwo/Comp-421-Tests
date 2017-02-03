//
// File containing testing utilities.
//

#include "utils.h"

void
print_stats(struct termstat *stats) {
    int i;
    for (i = 0; i < NUM_TERMINALS; i++) {
        printf("\nTERMINAL %d STATISTICS:\n", i);
        printf("\tCharacters in (tty_in): %d\n", stats[i].tty_in);
        printf("\tCharacters out (tty_out): %d\n", stats[i].tty_out);
        printf("\tUser characters written (user_in): %d\n", stats[i].user_in);
        printf("\tUser characters read (user_out): %d\n", stats[i].user_out);
    }
}

void
append_null(char *buf, int maxlen) {
    int j;

    for (j = 0; j < maxlen; j++) {
        if (buf[j] == '\n') {
            buf[j + 1] = '\0';
            break;
        }
    }
}