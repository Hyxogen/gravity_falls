#include "map.h"

hexagon_t	*gridrotate(hexagon_t *head, unsigned int rot)
{
	if (rot > 5)
		rot = rot % 6;
	if (head)
		while (rot--)
			head = gridrotate_once(head);
	return (head);
}

hexagon_t	*gridrotate_once(hexagon_t *head)
{
	hexagon_t	*next;

	next = head;
	while (next->sides[4])
		next = next->sides[4];
	hexiter(head, hexrotate);
	return (next);
}

void	hexiter(hexagon_t *head, void (*f)(hexagon_t *))
{
	hexagon_t	*hex;
	hexagon_t	*next;

	hex = head->sides[2];
	while (hex)
	{
		next = hex->sides[2];
		f(hex);
		hex = next;
	}
	hex = head->sides[4];
	while (hex)
	{
		next = hex->sides[4];
		f(hex);
		hex = next;
	}
	next = head->sides[3];
	f(head);
	if (next)
		hexiter(next, f);
}

void	hexrotate(hexagon_t *hex)
{
	hexagon_t	*tmp;

	tmp = hex->sides[5];
	for (int i = 5; i > 0; i--)
		hex->sides[i] = hex->sides[i - 1];
	hex->sides[0] = tmp;
}
