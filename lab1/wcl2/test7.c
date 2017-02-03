#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"


#define BUFLEN 80

void writer(void *);
void reader_writer(void *);

char string[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque tellus nisi, tempor id sem vitae, elementum aliquet ex. Fusce in bibendum massa, a sollicitudin libero. Sed dictum auctor ullamcorper. Mauris scelerisque laoreet eleifend. Vestibulum eget luctus magna, eget porttitor enim. Aenean vulputate erat in felis facilisis accumsan. Donec eu luctus sem. Proin quis molestie nibh. Donec pulvinar sem orci, vel pharetra nunc pulvinar non.Aliquam tempor tellus sit amet ante accumsan, vel volutpat enim tincidunt. Ut non dapibus justo. Interdum et malesuada fames ac ante ipsum primis in faucibus. Morbi eu viverra urna. Sed ornare vehicula nunc id molestie. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Nam ac tristique metus. Phasellus eleifend, risus sit amet condimentum sagittis, felis mauris dapibus urna, at pulvinar justo mi ut enim. Etiam vitae lorem efficitur, vulputate ipsum sed, hendrerit ligula. Mauris feugiat faucibus dui a ullamcorper. In laoreet pulvinar interdum. Duis ut sapien a lacus dictum pulvinar et quis quam. Sed sed ligula ligula.Quisque ut iaculis arcu. Proin ante tellus, gravida non ullamcorper eu, faucibus quis erat. Praesent vitae orci mauris. Curabitur ultricies eros ut quam tristique tempor. Donec egestas quam sed gravida commodo. Nunc ac mi volutpat, lacinia nibh aliquam, viverra dolor. Vestibulum facilisis purus quis libero iaculis, in faucibus sem elementum. Sed semper libero et sapien placerat lobortis. Donec quis ex nisi. Sed auctor purus et dictum cursus.Nullam at elit sit amet sem fringilla molestie nec eu nulla. Curabitur lectus mi, pellentesque ac maximus et, convallis a est. Aliquam viverra ex non facilisis scelerisque. Vestibulum a lacus sed purus sagittis euismod. Donec aliquet metus in eleifend fringilla. Pellentesque at pharetra ligula. Fusce erat urna, consequat eu vehicula et, scelerisque eu sapien. Proin aliquet, risus sit amet blandit elementum, lorem eros viverra tortor, nec feugiat quam erat eget ipsum. Nullam vel turpis ac leo feugiat viverra vitae ut sapien. Quisque sit amet dapibus nisl. Nullam vestibulum ullamcorper ante nec placerat. Sed bibendum in urna posuere lacinia. Donec consequat, ex et porta tincidunt, sem quam gravida magna, sit amet aliquet nibh nibh eu nisl. Integer vehicula, mi id pulvinar laoreet, risus magna ultrices nisi, vitae lacinia orci ligula nec nunc. Maecenas lacinia eu justo sed hendrerit. Vivamus ipsum ligula, pulvinar eu ullamcorper in, aliquet varius tellus. Pellentesque a accumsan nunc. Maecenas in urna placerat, laoreet dolor imperdiet, pellentesque urna. Phasellus neque lectus, euismod non consequat vitae, tempor sed nulla. Etiam nisi tortor, iaculis id sollicitudin nec, dignissim vitae orci. Pellentesque non erat ut risus maximus sodales ut a nulla. Nam vitae tortor a libero interdum scelerisque iaculis eget sapien. Maecenas in luctus sem, sed finibus elit. Nunc lobortis non mauris nec auctor. Vestibulum nec mollis tortor, sed pretium purus. Nam vel neque quis mi euismod euismod non id ante.";
int length = sizeof(string) - 1;
char *buf;

// Tests interplay of reading and writing, writing to other terminals at the same time.
int main(int argc, char **argv)
{
    int i;
    int term[] = {0, 1, 2, 3};

    InitTerminalDriver();
    InitTerminal(0);
    InitTerminal(1);
    InitTerminal(2);
    InitTerminal(3);

    if (argc > 1) HardwareOutputSpeed(0, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(0, atoi(argv[2]));


    for (i = 1; i < NUM_TERMINALS; i++) {
        ThreadCreate(writer, &term[i]);
    }

    ThreadCreate(reader_writer, NULL);

    ThreadWaitAll();

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);

    print_stats(stats);

    free(stats);

    sleep(10);

    exit(0);
}

void
writer(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    status = WriteTerminal(((int *)arg)[0], string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
reader_writer(void *arg)
{
    int status, i;
    int num_iters = 10;
    char hello_string[] = "\nHello, what's your name?\n";
    char welcome_string[] = "\nWelcome ";
    char end_string[] = "!\n";

    buf = malloc(sizeof(char) * BUFLEN);

    for (i = 0; i < num_iters; i++) {
        printf("Looping\n");
        WriteTerminal(0, hello_string, sizeof(hello_string) - 1);

        status = ReadTerminal(0, buf, BUFLEN - 1);

        // Append a null terminator.
        append_null(buf, BUFLEN - 1);

        printf("\nGot status: %d\n", status);
        printf("Read string: %s", buf);

        WriteTerminal(0, welcome_string, sizeof(welcome_string) - 1);
        WriteTerminal(0, buf, strlen(buf) - 1);
        WriteTerminal(0, end_string, sizeof(end_string) - 1);

    }

    free(buf);
    return;
}
