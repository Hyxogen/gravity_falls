#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
Return meanings:
	0: Nothing
	> 0: color which won.
	-1:	"Both won"
	-2:	"Draw: field is full"
	-3:	"Illegal move: column is already full"
	-4:	"Illegal move: Tile dropped outside of field"
*/	

#define WINLEN 3

typedef struct hexagon_s
{
	struct hexagon_s	*sides[6];
	int					color;
}						hexagon_t;

void		pgrid(hexagon_t *hex);

	//	hex.c
hexagon_t	*hexnew(void);
hexagon_t	*get_bottom_left(hexagon_t *head);
hexagon_t	*get_first_empty(hexagon_t *hex);
hexagon_t	*get_first_color(hexagon_t *hex);
hexagon_t	*get_column(hexagon_t *head, int column);
int			hexiter(hexagon_t *head, int (*f)(hexagon_t *, void *), void *param);
int			del(hexagon_t *hex, void *param);

	//	grid.c
hexagon_t	*gridcreate(int len);
hexagon_t	*hexrow(hexagon_t *orig, int side, int len);
void		hexrows(hexagon_t *hex, int height);
void		hexfill(hexagon_t *hex);
void		hexlinkrow(hexagon_t *hex, int side);
void		hexlink(hexagon_t *hex);
void		griddestroy(hexagon_t *head);

	//	win.c
int			isfull(hexagon_t *head);
int			isempty(hexagon_t *hex, void *param);
int			iswin(hexagon_t *hex, void *color);
int			win_row(hexagon_t *hex, int color, int side);
int			checkboard(hexagon_t *head, ...);
int			checkcolor(hexagon_t *head, void *color);

	//	drop.c
void		dropall(hexagon_t *head);
void		dropcolumn(hexagon_t *hex);
int			droptile(hexagon_t *head, int column, int color);

	//	rotate.c
void		gridrotate_once(hexagon_t **head);
int			gridrotate(hexagon_t **head, unsigned int rot);
int			hexrotate(hexagon_t *hex, void *param);

#endif
