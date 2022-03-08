#include "map.h"

int	iswin(hexagon_t *hex)
{
	if (win_row(hex, 0) || win_row(hex, 1) || win_row(hex, 2))
		return (1);
	return (0);
}

int	win_row(hexagon_t *hex, int side)
{
	int	opposite = side + 3;
	int	len = WINLEN - 1;

	while (hex->sides[side] && hex->color == hex->sides[side]->color)
		hex = hex->sides[side];
	while (hex->sides[opposite] && hex->color == hex->sides[opposite]->color && len--)
		hex = hex->sides[opposite];
	if (!len)
		return (1);
	return (0);
}

int	isfull(hexagon_t *head)
{
	if (!hexiter(head, isempty))
		return (1);
	return (0);
}

int	isempty(hexagon_t *hex)
{
	if (!hex->color)
		return (1);
	return (0);
}