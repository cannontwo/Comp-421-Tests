#ifndef COMP421_1_UTILS_H
#define COMP421_1_UTILS_H

#include <terminals.h>
#include <hardware.h>
#include <stdio.h>

// Print terminal statistics.
void print_stats(struct termstat *stats);

// Append a null character to the end of a character array. Note buf must have size at least maxlen + 1.
void append_null(char *buf, int maxlen);

#endif //COMP421_1_UTILS_H
