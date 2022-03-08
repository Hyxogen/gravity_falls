#include "map.h"

void	dropall(hexagon_t *head)
{
	head = get_bottom_left(head);
	dropcolumn(head);
}


void	dropcolumn(hexagon_t *hex)
{
	hexagon_t	*empty;

	while (hex->color)
	{
		hex = hex->sides[0];
		if (!hex)
			return ;
	}
	empty = hex;
	while (!hex->color)
		hex = hex->sides[0];
}

hexagon_t	*get_bottom_left(hexagon_t *head)
{
	while (head->sides[4])
		head = head->sides[4];
	while (head->sides[3])
		head = head->sides[3];
	return (head);
}

hexagon_t	*get_first_empty(hexagon_t *hex)
{
	while (hex && hex->color)
		hex = hex->sides[0];
	return (hex);
}