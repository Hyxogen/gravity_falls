#ifndef OPT_H
#define OPT_H

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "map.h"

/*
Flags:
	-f(bots): first bot (as path, so ./bot1)
	-g(bots): second bot (as path, so ./bot2)
	-c(color): colors to be used
	-s(size): board size, as sidelength
	-t(tiles): amount of tiles
	-v(victory): amount of tiles in a row needed to win
*/

void	opt_init(int argc, char **argv);
char	*getbot(int argc, char **argv);
int		getcolor(int argc, char **argv);
int		getsize(int argc, char **argv);
int		gettiles(int argc, char **argv);
int		getwinlen(int argc, char **argv);

#endif
