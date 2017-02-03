#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <terminals.h>

#include "utils.h"

void writer(void *);

// Tests carriage return handling.
int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(writer, NULL);

    ThreadWaitAll();

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);

    print_stats(stats);

    free(stats);

    exit(0);
}


void
writer(void *dummy)
{
    int i, j, n;
    int status;
    char buf[128];
    char *cp;
    int len;

    n = 0;
    for (i = 0; i < 10; i++)
    {
	cp = buf;
	for (j = 0; j < 5; j++)
	{
	    sprintf(cp, "%2d... ", ++n);
	    cp += strlen(cp);
	}
	strcpy(cp, "\n");
	len = cp - buf + 1;
	status = WriteTerminal(1, buf, len);
	if (status != len)
	    fprintf(stderr, "Error: writer status = %d, len = %d\n",
		status, len);
    }
}
