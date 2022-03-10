#ifndef OPT_H
#define OPT_H

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "map.h"

/*
Flags:
	-a(alarm): thinking time in millisecond
	-c(color): colors to be used. Colors need to be given last
	-f(bots): first bot (as path, so ./bot1)
	-g(bots): second bot (as path, so ./bot2)
	-s(size): board size, as sidelength
	-t(tiles): amount of tiles
	-v(victory): amount of tiles in a row needed to win

	For example:
	./cluster -a 100 -f ./bot1 -g ./bot2 -s 10 -t 500 -v 10 -c 3355647 3404031 16724787 16742195
*/

void	opt_init(int argc, char **argv);
char	*getbot(int argc, char **argv);
int		getcolor(int argc, char **argv);
int		getsize(int argc, char **argv);
int		gettiles(int argc, char **argv);
int		getwinlen(int argc, char **argv);
int		getthinkingtime(int argc, char **argv);

#endif
