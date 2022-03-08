#include "map.h"

int	iswin(hexagon_t *hex)
{
	if (win_row(hex, 0) || win_row(hex, 1) || win_row(hex, 2))
		return (1);
	return (0);
}

int	win_row(hexagon_t *hex, int side)
{
	int	opposite = side + 3;
	int	len = WINLEN - 1;

	while (hex->sides[side] && hex->color == hex->sides[side]->color)
		hex = hex->sides[side];
	while (hex->sides[opposite] && hex->color == hex->sides[opposite]->color && len--)
		hex = hex->sides[opposite];
	if (!len)
		return (1);
	return (0);
}

int	isfull(hexagon_t *head)
{
	if (!hexiter(head, isempty, 0))
		return (1);
	return (0);
}

int	isempty(hexagon_t *hex, void *param)
{
	(void)param;
	if (!hex->color)
		return (1);
	return (0);
}

int	checkboard(hexagon_t *head, ...)
{
	static int	colors[2];
	int			ret = 0;

	if (!colors[0])
	{
		va_list	ap;
		va_start(ap, head);
		colors[0] = va_arg(ap, int);
		colors[1] = va_arg(ap, int);
		va_end(ap);
		return (0);
	}
	ret += hexiter(head, checkcolor, &colors[0]);
	ret += hexiter(head, checkcolor, &colors[1]);
	return (ret);
}

int	checkcolor(hexagon_t *head, void *color)
{
	return (0);
}
