#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define HEX_SIZE 2.0f
#define HEX_CONST 1.7320508f
#define HEX_LEN_CONST 2.3094010f

#define max(a, b) (a < b ? b : a)

float _hex_sdf(int x, int y, int size) {
	x = abs(x);
	y = abs(y);
	return max(x * 0.5f * HEX_CONST + y * 0.5f, y) - size;
}

void render_hexf(imbuffer_t *buffer, int hex_x, int hex_y, int size, color_t color) {
	int width, height;
	int hsize;
	int x, y;

	width = size * HEX_LEN_CONST;
	height = size * HEX_LEN_CONST;
	hsize = size / 2;
	for (y = -size * HEX_LEN_CONST; y < height; y++) {
		for (x = -size * HEX_LEN_CONST; x < width; x++) {
			if (_hex_sdf(x, y, hsize) <= 0.0f)
				ib_putp(buffer, hex_x + x, hex_y + y, color);
		}
	}
}

void render_hexh(imbuffer_t *buffer, int hex_x, int hex_y, int size, int line_width, color_t color) {
	int width, height;
	int hsize;
	int x, y;
	float dist;

	width = size * HEX_LEN_CONST;
	height = size * HEX_LEN_CONST;
	hsize = size / 2;
	for (y = -size * HEX_LEN_CONST; y < height; y++) {
		for (x = -size * HEX_LEN_CONST; x < width; x++) {
			dist = _hex_sdf(x, y, hsize);
			if (dist >= -line_width && dist <= 0.0f)
				ib_putp(buffer, hex_x + x, hex_y + y, color);
		}
	}
}

void _render_hex_column(imbuffer_t *buffer, int x, int y, int size, int line_width, const hexagon_t *top, color_t color) {
	for (; top; top = top->sides[3]) {
		render_hexh(buffer, x, y, size, line_width, color);
		if (top->color)
			render_hexf(buffer, x, y, size - 2, top->color);
		y += size + 2 * line_width;
	}
}

#define hex_size(x) 0

void render_map(imbuffer_t *buffer, int x, int y, int size, int line_width, const hexagon_t *map, color_t color) {
	hexagon_t *hex;
	int xoff, yoff;
	int hsize;

	hsize = size / 2;
	xoff = size - hex_size(size / 2.0f);
	yoff = hsize;
	_render_hex_column(buffer, x, y, size, line_width, map, color);
	for (hex = map->sides[2]; hex; hex = hex->sides[2]) {
		_render_hex_column(buffer, x + xoff, y + yoff, size, line_width, hex, color);
		xoff += size - hex_size(size / 2.0f);
		yoff += hsize;
	}
	xoff = -size + hex_size(size / 2.0f);
	yoff = hsize;
	for (hex = map->sides[4]; hex; hex = hex->sides[4]) {
		_render_hex_column(buffer, x + xoff, y + yoff, size, line_width, hex, color);
		xoff -= size + hex_size(size / 2.0f);
		yoff += hsize;
	}
}
