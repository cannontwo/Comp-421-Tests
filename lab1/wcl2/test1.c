#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <terminals.h>
#include <hardware.h>

#include "utils.h"

// Tests initialization.
int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);

    print_stats(stats);

    sleep(3);

    free(stats);
    exit(0);
}
