#include "map.h"

hexagon_t	*getgrid(int len)
{
	hexagon_t	*hex;

	hex = hexnew();
	hex->sides[2] = hexrow(hex, 2, len - 1);
	hex->sides[4] = hexrow(hex, 4, len - 1);
	hexrows(hex, 2 * (len - 1));
	hexfill(hex->sides[3]);
	return (hex);
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

void	hexrows(hexagon_t *hex, int height)
{
	if (hex->sides[2])
		hexrows(hex->sides[2], height - 1);
	if (!hex->sides[3])
		hex->sides[3] = hexrow(hex, 3, height);
	if (hex->sides[4])
		hexrows(hex->sides[4], height - 1);
}

void	hexfill(hexagon_t *hex)
{
	if (!hex)
		return ;
	hexlink(hex);
	hexlinkrow(hex, 1);
	hexlinkrow(hex, 5);
	if (hex->sides[3])
		hexfill(hex->sides[3]);
}

void	hexlinkrow(hexagon_t *hex, int side)
{
	while (hex->sides[side])
	{
		if (!hex->sides[side]->sides[3])
			return ;
		hex = hex->sides[side]->sides[3];
		hexlink(hex);
	}
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

void	pgrid(hexagon_t *hex)
{
	if (!hex)
		return ;
	printf("------Hex: %p-------\n", (void*) hex);
	printf("Up: %p\n", (void*) hex->sides[0]);
	printf("Up-right: %p\n", (void*) hex->sides[1]);
	printf("Down-right: %p\n", (void*) hex->sides[2]);
	printf("Down: %p\n", (void*) hex->sides[3]);
	printf("Down-left: %p\n", (void*) hex->sides[4]);
	printf("Up-left: %p\n", (void*) hex->sides[5]);
	printf("Color: 0x%08X\n", hex->color);
	printf("\n");
	pgrid(hex->sides[3]);
}
