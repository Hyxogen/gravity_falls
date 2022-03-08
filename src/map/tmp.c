#include "map.h"

int	main(void)
{
	hexagon_t	*head;

	head = getgrid(2);
	pgrid(head->sides[4]);
	pgrid(head);
	pgrid(head->sides[2]);
}