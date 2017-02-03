#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

#include "utils.h"

#define BUFLEN 80

void reader1(void *);

char *buf;

// Tests reading.
int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(reader1, NULL);

    ThreadWaitAll();

    sleep(10);

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);

    print_stats(stats);

    free(stats);

    exit(0);
}

void
reader1(void *arg)
{
    int status, i;
    int num_iters = 10;

    buf = malloc(sizeof(char) * BUFLEN);

    for (i = 0; i < num_iters; i++) {
        status = ReadTerminal(1, buf, BUFLEN - 1);

        // Append a null terminator.
        append_null(buf, BUFLEN - 1);

        printf("\nGot status: %d\n", status);
        printf("Read string: %s", buf);
    }

    free(buf);
}
