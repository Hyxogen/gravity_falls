#include "map.h"

int	droptile(hexagon_t *hex, int column, int color)
{
	hex = getcolumn(hex, column);
	if (!hex)
		return (1);
	if (hex->color)
		return (2);
	while (hex->sides[3] && !hex->sides[3]->color)
		hex = hex->sides[3];
	hex->color = color;
	if (win(hex))
		return (3);
	return (0);
}

hexagon_t	*getcolumn(hexagon_t *head, int column)
{
	while (column < 0)
	{
		head = head->sides[4];
		if (!head)
			return (NULL);
		column++;
		if (!column)
			return (head);
	}
	while (column > 0)
	{
		head = head->sides[2];
		if (!head)
			return (NULL);
		column--;
		if (!column)
			return (head);
	}
	return (head);
}

int	win(hexagon_t *hex)
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
