#include "map.h"

void	dropall(hexagon_t *head)
{
	head = get_bottom_left(head);
	while (head->sides[2])
	{
		dropcolumn(head);
		head = head->sides[2];
	}
	while (head->sides[1])
	{
		dropcolumn(head);
		head = head->sides[1];
	}
}

void	dropcolumn(hexagon_t *hex)
{
	hexagon_t	*filled;

	while (1)
	{
		hex = get_first_empty(hex);
		filled = get_first_color(hex);
		if (!hex || !filled)
			return ;
		hex->color = filled->color;
		filled->color = 0;
	}
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

hexagon_t	*get_first_color(hexagon_t *hex)
{
	while (hex && !hex->color)
		hex = hex->sides[0];
	return (hex);
}
