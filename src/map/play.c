#include "map.h"

int	droptile(hexagon_t *head, int column, int color)
{
	head = getcolumn(head, column);
	if (!head)
		return (1);
	if (head->color)
		return (2);
	while (head->sides[3] && !head->sides[3]->color)
		head = head->sides[3];
	head->color = color;
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
