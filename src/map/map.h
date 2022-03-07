#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct hexagon_s
{
	struct hexagon_s	*sides[6];
	int					color;
}						hexagon_t;

hexagon_t	*getgrid(int len);
hexagon_t	*hexnew(void);
hexagon_t	*hexrow(hexagon_t *orig, int side, int len);
void		hexrows(hexagon_t *hex, int height);
void		hexfill(hexagon_t *hex);
void		hexlink(hexagon_t *hex);
void		pgrid(hexagon_t *hex);

hexagon_t	*gridrotate(hexagon_t *grid, unsigned int rot);
hexagon_t	*gridrotate_once(hexagon_t *hex);
void		linerotate(hexagon_t *hex);

#endif
