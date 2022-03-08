#include "map.h"

int	dropall(hexagon_t *head)
{
	head = get_bottom_left(head);
	while (head->sides[2])
	{
		if (dropcolumn(head))
			return (1);
		head = head->sides[2];
	}
	while (head->sides[1])
	{
		if (dropcolumn(head))
			return (1);
		head = head->sides[1];
	}
	return (0);
}

int	dropcolumn(hexagon_t *hex)
{
	hexagon_t	*filled;

	while (1)
	{
		hex = get_first_empty(hex);
		filled = get_first_color(hex);
		if (!hex || !filled)
			return (0);
		hex->color = filled->color;
		filled->color = 0;
		if (win(hex))
			return (1);
	}
	return (0);
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
