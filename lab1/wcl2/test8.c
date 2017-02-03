#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

#include "utils.h"


void writer1(void *);
void writer2(void *);

char string1[] = "Meditation blog next level, cardigan health goth pabst +1 organic ugh bicycle rights disrupt four dollar toast flexitarian put a bird on it. Neutra tousled gastropub, woke brunch meh lyft butcher activated charcoal cornhole cold-pressed bushwick messenger bag fam mustache. Polaroid XOXO disrupt yr williamsburg hexagon. Banjo cliche viral biodiesel chartreuse hexagon meh. Pinterest YOLO man braid small batch, tote bag art party try-hard asymmetrical banh mi crucifix trust fund squid master cleanse. Cronut echo park freegan YOLO four loko, poke marfa lomo craft beer swag chicharrones asymmetrical. La croix church-key brooklyn, cred coloring book ennui craft beer 90's street art salvia.";
char string2[] = "Farm-to-table coloring book tilde brooklyn street art pok pok, you probably haven't heard of them iPhone tattooed kogi craft beer DIY poutine sustainable bushwick. Pitchfork vinyl vexillologist heirloom brooklyn listicle. Portland marfa microdosing pour-over, tote bag post-ironic cornhole franzen yuccie fingerstache raclette stumptown messenger bag. Godard salvia woke ramps jianbing, schlitz actually 3 wolf moon asymmetrical lo-fi man bun photo booth. Vinyl cred direct trade, church-key marfa tousled williamsburg 3 wolf moon enamel pin. Cornhole pug tousled next level, meditation neutra occupy vexillologist lo-fi deep v. Pok pok brunch echo park, poke irony direct trade flannel sriracha unicorn lumbersexual intelligentsia mumblecore humblebrag.";
int length1 = sizeof(string1) - 1;
int length2 = sizeof(string2) - 1;

// Tests sequential writing of concurrent write requests.
int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(writer1, NULL);
    ThreadCreate(writer2, NULL);

    ThreadWaitAll();

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);

    print_stats(stats);

    free(stats);

    sleep(10);

    exit(0);
}

void
writer1(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    status = WriteTerminal(1, string1, length1);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
writer2(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    status = WriteTerminal(1, string2, length2);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}
