#include <stdio.h>
#include "stdlib.h"
#include "map.h"

int	main(int argc, char *argv[])
{
	hexagon_t	*hex;
	int			len = 0;

	if (argc < 2)
		return (1);
	while (*argv[1])
		len = len * 10 + *(argv[1])++ - '0';
	hex = hexnew();
	hex->sides[2] = hexrow(hex, 2, len - 1);
	hex->sides[4] = hexrow(hex, 4, len - 1);
	hexrows(hex, 2 * (len - 1));
	hexfill(hex);
	pgrid(hex);
	pgrid(hex->sides[2]);
	pgrid(hex->sides[2]->sides[2]);
	pgrid(hex->sides[4]);
	pgrid(hex->sides[4]->sides[4]);
	exit(EXIT_SUCCESS);
}

void	hexfill(hexagon_t *hex)
{
	hexlink(hex);
	if (hex->sides[1])
		if (hex->sides[1]->sides[3])
			hexfill(hex->sides[1]->sides[3]);
	if (hex->sides[5])
		if (hex->sides[5]->sides[3])
			hexfill(hex->sides[5]->sides[3]);
	if (hex->sides[3])
		hexfill(hex->sides[3]);
}

void	hexrows(hexagon_t *hex, int height)
{
	if (hex->sides[2])
		hexrows(hex->sides[2], height - 1);
	if (!hex->sides[3])
		hex->sides[3] = hexrow(hex, 3, height);
	if (hex->sides[4])
		hexrows(hex->sides[4], height - 1);
}

hexagon_t	*hexrow(hexagon_t *orig, int side, int len)
{
	hexagon_t	*new;
	int			opposite;

	if (!len)
		return (NULL);
	new = hexnew();
	if (side < 3)
		opposite = side + 3;
	else
		opposite = side - 3;
	new->sides[opposite] = orig;
	new->sides[side] = hexrow(new, side, len - 1);
	return (new);
}

hexagon_t	*hexnew(void)
{
	hexagon_t	*new;
	int			i;

	new = malloc(sizeof(*new));
	for (i = 0; i < 6; i++)
		new->sides[i] = 0;
	new->color = 0;
	return (new);
}

void	pgrid(hexagon_t *hex)
{
	if (!hex)
		return ;
	printf("------Hex: %p-------\n", hex);
	printf("Up: %p\n", hex->sides[0]);
	printf("Up-right: %p\n", hex->sides[1]);
	printf("Down-right: %p\n", hex->sides[2]);
	printf("Down: %p\n", hex->sides[3]);
	printf("Down-left: %p\n", hex->sides[4]);
	printf("Up-left: %p\n", hex->sides[5]);
	pgrid(hex->sides[3]);
}

void	hexlink(hexagon_t *hex)
{
	if (!hex->sides[0])
		return ;
	if (hex->sides[0]->sides[2])
	{
		hex->sides[0]->sides[2]->sides[4] = hex;
		hex->sides[1] = hex->sides[0]->sides[2];
	}
	if (hex->sides[0]->sides[4])
	{
		hex->sides[0]->sides[4]->sides[2] = hex;
		hex->sides[5] = hex->sides[0]->sides[4];
	}
}
