#include "map.h"

#define BLUE 0x000000FF
#define RED 0x00FF0000

int	main(void)
{
	hexagon_t	*head;

	checkboard(0, BLUE, RED);
	head = gridcreate(3);
	printf("%d\n", droptile(head, -2, 1));
	printf("%d\n", droptile(head, -1, 2));
	printf("%d\n", droptile(head, 0, 3));
	printf("%d\n", droptile(head, 0, 1));
	printf("%d\n", droptile(head, 1, 2));
	printf("%d\n", gridrotate(&head, 4));
	/*
	pgrid(head);
	printf("================================\n");
	pgrid(head->sides[2]);
	printf("================================\n");
	pgrid(head->sides[2]->sides[2]);
	*/
	griddestroy(head);
}

void	pgrid(hexagon_t *hex)
{
	if (!hex)
		return ;
	printf("------Hex: %p-------\n", (void*) hex);
	printf("Up: %p\n", (void*) hex->sides[0]);
	printf("Up-right: %p\n", (void*) hex->sides[1]);
	printf("Down-right: %p\n", (void*) hex->sides[2]);
	printf("Down: %p\n", (void*) hex->sides[3]);
	printf("Down-left: %p\n", (void*) hex->sides[4]);
	printf("Up-left: %p\n", (void*) hex->sides[5]);
	printf("Color: 0x%08X\n", hex->color);
	printf("\n");
	pgrid(hex->sides[3]);
}
