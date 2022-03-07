#include <stdio.h>
#include "stdlib.h"

typedef struct s_hexagon
{
	struct s_hexagon	*sides[6];
	int					color;
}						t_hexagon;

t_hexagon	*hexrow(t_hexagon *orig, int side, int amount);
t_hexagon	*hexnew(void);
t_hexagon	*hex_getupright(t_hexagon *hex);
t_hexagon	*hex_getupleft(t_hexagon *hex);
void		pgrid(t_hexagon *hex);

int	main(int argc, char *argv[])
{
	t_hexagon	*top;
	int			side = 0;

	if (argc < 2)
		return (1);
	while (*argv[1])
		side = side * 10 + *(argv[1])++ - '0';
	top = hexnew();
	top->sides[2] = hexrow(top, 2, side - 2);
	top->sides[3] = hexrow(top, 3, side - 2);
	top->sides[4] = hexrow(top, 4, side - 2);
	pgrid(top);
	return (0);
}

t_hexagon	*hexrow(t_hexagon *orig, int side, int amount)
{
	t_hexagon	*new;
	int			opposite;

	new = hexnew();
	if (side < 3)
		opposite = side + 3;
	else
		opposite = side - 3;
	new->sides[opposite] = orig;
	if (amount)
		new->sides[side] = hexrow(new, side, amount - 1);
	return (new);
}

t_hexagon	*hexnew(void)
{
	t_hexagon	*new;
	int			i;

	new = malloc(sizeof(*new));
	for (i = 0; i < 6; i++)
		new->sides[i] = 0;
	new->color = 0;
	return (new);
}

void	pgrid(t_hexagon *hex)
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

t_hexagon	*hex_getupright(t_hexagon *hex)
{
	return (hex->sides[0]->sides[2]);
}

t_hexagon	*hex_getupleft(t_hexagon *hex)
{
	return (hex->sides[0]->sides[4]);
}