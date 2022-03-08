#ifndef GFX_H
#define GFX_H

#include <sys/types.h>
#include "map/map.h"

#define gfx_init() mlx_init()
#define win_putp(win, x, y, color) ib_putp(&win->image, x, y, color)

#define COLOR_ALPHA_OFFSET 24
#define COLOR_RED_OFFSET 16
#define COLOR_GREEN_OFFSET 8
#define COLOR_BLUE_OFFSET 0

#define COLOR_ALPHA_MASK	0xff000000
#define COLOR_RED_MASK		0x00ff0000
#define COLOR_GREEN_MASK	0x0000ff00
#define COLOR_BLUE_MASK		0x000000ff

#define COLOR_BLUE	0x000000FF
#define COLOR_RED	0x00FF0000
#define COLOR_GREEN	0x0000FF00

typedef struct imbuffer imbuffer_t;
typedef struct screen screen_t;
typedef struct window window_t;

typedef int (*win_update_proc)(void*);

struct imbuffer {
	void *mlx;
	void *handle;
	char *addr;
	int width;
	int height;
	int line_width;
	int bpp;
	int endian;
};

struct window {
	void *mlx;
	void *handle;
	void *usr_ptr;
	int width;
	int height;
	imbuffer_t image;
};

typedef int	color_t;

color_t	color_encode(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue);

/*void *gfx_init(void);*/

void win_new(window_t *window, const char *title, int width, int height, void *mlx);
void win_destroy(window_t *window);

void win_setptr(window_t *window, void *ptr);
void win_start(window_t *window, win_update_proc proc);
void win_update(window_t *window);

void ib_new(imbuffer_t *buffer, void *mlx, int width, int height);
void ib_destroy(imbuffer_t *buffer);

void ib_putp(imbuffer_t *buffer, int x, int y, color_t color);

void ib_flush(window_t *out, const imbuffer_t *buffer);

void render_hexf(imbuffer_t *buffer, int hex_x, int hex_y, int size, color_t color);
void render_hexh(imbuffer_t *buffer, int hex_x, int hex_y, int size, int line_width, color_t color);
void render_map(imbuffer_t *buffer, int x, int y, int size, int line_width, const hexagon_t *map, color_t color);
#endif
