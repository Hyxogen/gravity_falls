#include "map.h"

int	droptile(hexagon_t *head, int column, int color)
{
	hexagon_t	*hex;

	hex = get_column(head, column);
	if (!hex)
		return (3);
	if (hex->color)
		return (4);
	while (hex->sides[3] && !hex->sides[3]->color)
		hex = hex->sides[3];
	hex->color = color;
	if (iswin(hex))
		return (1);
	if (isfull(head))
		return (2);
	return (0);
}

int	dropall(hexagon_t *head)
{
	int	ret = 0;

	head = get_bottom_left(head);
	while (head->sides[2])
	{
		if (dropcolumn(head))
			ret = 1;
		head = head->sides[2];
	}
	while (head->sides[1])
	{
		if (dropcolumn(head))
			ret = 1;
		head = head->sides[1];
	}
	return (ret);
}

int	dropcolumn(hexagon_t *hex)
{
	hexagon_t	*filled;
	int			ret = 0;

	while (1)
	{
		hex = get_first_empty(hex);
		filled = get_first_color(hex);
		if (!hex || !filled)
			return (0);
		hex->color = filled->color;
		filled->color = 0;
		if (iswin(hex))
			ret = 1;
	}
	return (ret);
}
