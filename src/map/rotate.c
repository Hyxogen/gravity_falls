#include "map.h"

hexagon_t	*gridrotate(hexagon_t *grid, unsigned int rot)
{
	if (grid)
		while (rot--)
			grid = gridrotate_once(grid);
	return (grid);
}

hexagon_t	*gridrotate_once(hexagon_t *hex)
{
	hexagon_t	*head;
	hexagon_t	*next;

	while (hex)
	{
		head = hex;
		next = hex->sides[4];
		linerotate(hex);
		hex = next;
	}
	hex = head->sides[2];
	while (hex)
	{
		next = hex->sides[2];
		linerotate(hex);
		hex = next;
	}
	return (head);
}

void	linerotate(hexagon_t *hex)
{
	hexagon_t	*tmp;

	tmp = hex->sides[0];
	for (int i = 0; i < 5; i++)
		hex->sides[i] = hex->sides[i + 1];
	hex->sides[5] = tmp;
	if (hex->sides[1])
		linerotate(hex->sides[1]);
}

int		main(void)
{
	hexagon_t	*grid = getgrid(2);

	printf("### Left column:\n");
	pgrid(grid->sides[4]);
	printf("### Middle column:\n");
	pgrid(grid);
	printf("### Right column:\n");
	pgrid(grid->sides[2]);
	grid = gridrotate(grid, 1);
	printf("=== New grid === \n");
	printf("### Left column:\n");
	pgrid(grid->sides[4]);
	printf("### Middle column:\n");
	pgrid(grid);
	printf("### Right column:\n");
	pgrid(grid->sides[2]);
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
	printf("\n");
	pgrid(hex->sides[3]);
}
