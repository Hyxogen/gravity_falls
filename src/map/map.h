#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

	//	Return meanings:
	//	1:	"Win: someone won"
	//	2:	"Draw: field is full"
	//	3:	"Illegal move: Tile dropped outside of field"
	//	4:	"Illegal move: column is already full"
	//	5:	"Draw: both players won"

#define WINLEN 4

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
int			hexiter(hexagon_t *head, int (*f)(hexagon_t *));

	//	play.c
int			win_row(hexagon_t *hex, int side);
int			iswin(hexagon_t *hex);
int			isfull(hexagon_t *head);
int			isempty(hexagon_t *hex);

	//	drop.c
int			droptile(hexagon_t *hex, int column, int color);
int			dropall(hexagon_t *head);
int			dropcolumn(hexagon_t *hex);

	//	grid.c
hexagon_t	*getgrid(int len);
hexagon_t	*hexrow(hexagon_t *orig, int side, int len);
void		hexrows(hexagon_t *hex, int height);
void		hexfill(hexagon_t *hex);
void		hexlinkrow(hexagon_t *hex, int side);
void		hexlink(hexagon_t *hex);

	//	rotate.c
void		gridrotate_once(hexagon_t **head);
int			gridrotate(hexagon_t **head, unsigned int rot);
int			hexrotate(hexagon_t *hex);

#endif
