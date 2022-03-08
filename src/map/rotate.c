#include "map.h"

int	gridrotate(hexagon_t **head, unsigned int rot)
{
	if (!*head)
		return (-1);
	if (rot > 5)
		rot = rot % 6;
	while (rot--)
		gridrotate_once(head);
	dropall(*head);
	return (checkboard(head));
}

void	gridrotate_once(hexagon_t **head)
{
	hexagon_t	*next;

	next = *head;
	while (next->sides[4])
		next = next->sides[4];
	hexiter(*head, hexrotate, 0);
	*head = next;
}

int	hexrotate(hexagon_t *hex)
{
	hexagon_t	*tmp;
	int			i;

	tmp = hex->sides[5];
	for (i = 5; i > 0; i--)
		hex->sides[i] = hex->sides[i - 1];
	hex->sides[0] = tmp;
	return (0);
}
