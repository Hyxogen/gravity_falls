#include "opt.h"

extern char *optarg;

void	opt_init(int argc, char **argv)
{
	win_row(0, 0, 0, argc, argv);
	checkboard(0, argc, argv);
}

char	*getbot(int argc, char **argv)
{
	static int	flag;
	static char bot[6] = "./bot";
	char		c;

	optind = 1;
	while ((c = getopt(argc, argv, "b:c:s:t:v:")) != -1)
	{
		if (c == 'b')
		{
			if (flag)
				return (argv[optind]);
			flag = 1;
			return (optarg);
		}
	}
	return (bot);
}

int		getsize(int argc, char **argv)
{
	char	c;

	optind = 1;
	while ((c = getopt(argc, argv, "b:c:s:t:v:")) != -1)
		if (c == 's')
			return (atoi(optarg));
	return (5);
}

int		gettiles(int argc, char **argv)
{
	char	c;

	optind = 1;
	while ((c = getopt(argc, argv, "b:c:s:t:v:")) != -1)
		if (c == 't')
			return (atoi(optarg));
	return (30);
}

int		getcolor(int argc, char **argv)
{
	static int	flag;
	int			colors[4] = { 0x3333FF, 0x33F0FF, 0xFF3333, 0xFF7733 };
	char		c;

	if (flag > 3)
		flag = 0;
	optind = 1;
	while ((c = getopt(argc, argv, "b:c:s:t:v:")) != -1)
	{
		if (c == 'c')
		{
			optind--;
			if (!argv[optind + flag] || *argv[optind + flag] == '-')
				break ;
			colors[flag] = atoi(argv[optind + flag]);
			break ;
		}
	}
	return (colors[flag++]);
}

int	getwinlen(int argc, char **argv)
{
	char	c;

	optind = 1;
	while ((c = getopt(argc, argv, "b:c:s:t:v:")) != -1)
		if (c == 'v')
			return (atoi(optarg));
	return (4);
}
