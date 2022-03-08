#include "map.h"

hexagon_t	*hexnew(void)
{
	hexagon_t	*new;
	int			i;

	new = malloc(sizeof(*new));
	for (i = 0; i < 6; i++)
		new->sides[i] = 0;
	new->color = 0;
	return (new);
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

hexagon_t	*get_column(hexagon_t *head, int column)
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

int	hexiter(hexagon_t *head, int (*f)(hexagon_t *))
{
	hexagon_t	*hex;
	hexagon_t	*next;
	int			ret = 0;

	hex = head->sides[2];
	while (hex)
	{
		next = hex->sides[2];
		ret += f(hex);
		hex = next;
	}
	hex = head->sides[4];
	while (hex)
	{
		next = hex->sides[4];
		ret += f(hex);
		hex = next;
	}
	next = head->sides[3];
	ret += f(head);
	if (next)
		ret += hexiter(next, f);
	return (ret);
}
