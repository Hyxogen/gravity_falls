#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

	//	Error messages:
	//	1:	"Tile dropped outside of field!\n"
	//	2:	"Column is already full!\n"

typedef struct hexagon_s
{
	struct hexagon_s	*sides[6];
	int					color;
}						hexagon_t;

	//	play.c
hexagon_t	*getcolumn(hexagon_t *head, int column);
int			droptile(hexagon_t *head, int column, int color);

	//	drop.c
hexagon_t	*get_bottom_left(hexagon_t *head);
hexagon_t	*get_first_empty(hexagon_t *hex);
void		dropall(hexagon_t *head);
void		dropcolumn(hexagon_t *hex);

	//	grid.c
hexagon_t	*getgrid(int len);
hexagon_t	*hexnew(void);
hexagon_t	*hexrow(hexagon_t *orig, int side, int len);
void		hexrows(hexagon_t *hex, int height);
void		hexfill(hexagon_t *hex);
void		hexlinkrow(hexagon_t *hex, int side);
void		hexlink(hexagon_t *hex);
void		pgrid(hexagon_t *hex);

	//	rotate.c
hexagon_t	*gridrotate(hexagon_t *grid, unsigned int rot);
hexagon_t	*gridrotate_once(hexagon_t *hex);
void		hexiter(hexagon_t *head, void (*f)(hexagon_t *));
void		hexrotate(hexagon_t *hex);

#endif
