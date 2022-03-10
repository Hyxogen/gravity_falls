#include "map.h"
#include "opt.h"

int	iswin(hexagon_t *hex, void *color)
{
	if (win_row(hex, *(int *)color, 0)
	 || win_row(hex, *(int *)color, 1)
	 || win_row(hex, *(int *)color, 2))
		return (1);
	return (0);
}

int	win_row(hexagon_t *hex, int color, int side, ...)
{
	static int	winlen = -1;
	int			len;

	if (winlen < 0)
	{
		va_list	ap;
		va_start(ap, side);
		winlen = getwinlen(va_arg(ap, int), va_arg(ap, void *));
		va_end(ap);
		if (winlen)
			winlen--;
		return (0);
	}
	len = winlen;
	if (hex->color != color)
		return (0);
	while (hex->sides[side] && color == hex->sides[side]->color)
		hex = hex->sides[side];
	while (hex->sides[side + 3] && color == hex->sides[side + 3]->color && len--)
		hex = hex->sides[side + 3];
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
	int			color[4] = { 0 };
	int			ret = 0;
	int			i;

	if (!colors[0])
	{
		va_list	ap;
		va_start(ap, head);
		int		argc = va_arg(ap, int);
		char	**argv = va_arg(ap, void *);
		for (i = 0; i < 4; i++)
			colors[i] = getcolor(argc, argv);
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
