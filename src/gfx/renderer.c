#include "gfx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define HEX_SIZE 2.0f
#define HEX_CONST 1.7320508f

#define max(a, b) (a < b ? b : a)

float _hex_sdf(int x, int y, int hex_x, int hex_y) {
	x = abs(hex_x - x);
	y = abs(hex_y - y);

	return max(x * 0.38f * HEX_CONST + y * 0.38f, y) - HEX_SIZE;
}

void _render_hex(imbuffer_t *buffer, int hex_x, int hex_y, char val) {
	int width, height;
	int x, y;

	width = buffer->width;
	height = buffer->height;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (_hex_sdf(x, y, hex_x, hex_y) <= 0.0f)
				ib_putb(buffer, x, y, (unsigned char) val);
		}
	}
}

void render_hex(imbuffer_t *buffer, int x , int y, const hexagon_t *hex) {
	if (hex == NULL)
		return;
	_render_hex(buffer, x, y, '@');
	render_hex(buffer, x, y - 2, hex->sides[0]);
	render_hex(buffer, x + 2, y - 2, hex->sides[1]);
	render_hex(buffer, x + 2, y, hex->sides[2]);
	render_hex(buffer, x + 2, y + 2, hex->sides[3]);
	render_hex(buffer, x, y + 2, hex->sides[4]);
	render_hex(buffer, x - 2, y + 2, hex->sides[5]);
}

void render_map(imbuffer_t *buffer, const hexagon_t *map) {
	render_hex(buffer, 2, 2, map);
}
