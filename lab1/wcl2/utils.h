#include <terminals.h>
#include <hardware.h>
#include <stdio.h>

// Print terminal statistics
void print_stats(struct termstat *stats);

// Append a null character to the end of a character array which is assumed to terminate
// with a newline. Note buf must have size at least maxlen - 1.
void append_null(char *buf, int maxlen);