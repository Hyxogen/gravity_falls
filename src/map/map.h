#ifndef MAP_H
#define MAP_H

typedef struct hexagon_s
{
	struct hexagon_s	*sides[6];
	int					color;
}						hexagon_t;

void		hexrows(hexagon_t *hex, int height);
hexagon_t	*hexrow(hexagon_t *orig, int side, int len);
hexagon_t	*hexnew(void);
void		hexfill(hexagon_t *hex);
void		hexlink(hexagon_t *hex);
void		pgrid(hexagon_t *hex);

#endif
