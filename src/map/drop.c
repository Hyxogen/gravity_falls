#include "map.h"

int	droptile(hexagon_t *head, int column, int color)
{
	hexagon_t	*hex;

	hex = get_column(head, column);
	if (!hex)
		return (-4);
	if (hex->color)
		return (-3);
	while (hex->sides[3] && !hex->sides[3]->color)
		hex = hex->sides[3];
	hex->color = color;
	if (iswin(hex, &hex->color))
		return (color);
	if (isfull(head))
		return (-2);
	return (0);
}

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
	dropcolumn(head);
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
