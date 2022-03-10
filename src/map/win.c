#include "map.h"

int	iswin(hexagon_t *hex, void *color)
{
	if (win_row(hex, *(int *)color, 0)
	 || win_row(hex, *(int *)color, 1)
	 || win_row(hex, *(int *)color, 2))
		return (1);
	return (0);
}

int	win_row(hexagon_t *hex, int color, int side)
{
	int	opposite = side + 3;
	int	len = WINLEN - 1;

	if (hex->color != color)
		return (0);
	while (hex->sides[side] && color == hex->sides[side]->color)
		hex = hex->sides[side];
	while (hex->sides[opposite] && color == hex->sides[opposite]->color && len--)
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
	static int	colors[4];
	int			color[4] = {};
	int			ret = 0;
	int			i;

	if (!colors[0])
	{
		va_list	ap;
		va_start(ap, head);
		colors[0] = va_arg(ap, int);
		colors[1] = va_arg(ap, int);
		colors[2] = va_arg(ap, int);
		colors[3] = va_arg(ap, int);
		va_end(ap);
		return (0);
	}
	for (i = 0; i < 4; i++)
		if (hexiter(head, iswin, &colors[i]))
			color[i] = colors[i];
	if (color[0] || color[1])
		ret++;
	if (color[2] || color[3])
		ret++;
	switch (ret)
	{
		case (1):
			for (i = 0; i < 4; i++)
				if (color[i])
					return (color[i]);
		case (2):
			return (-1);
		default:
			return (0);
	}
}
