#include "gfx.h"

#include "util/memory.h"
#include "util/assert.h"
#include <stdlib.h>
#include <string.h>
#include <mlx.h>

#define encode_color(handle, color) mlx_get_color_value(handle, color)

void ib_new(imbuffer_t *buffer, void *mlx, int width, int height) {
	buffer->width = width;
	buffer->height = height;
	buffer->mlx = mlx;
	buffer->handle = mlx_new_image(mlx, width, height);
	gf_assert(buffer->handle);
	buffer->addr = mlx_get_data_addr(buffer->handle, &(buffer->bpp), &(buffer->line_width), &(buffer->endian));
	gf_assert(buffer->addr);
}

void ib_destroy(imbuffer_t *buffer) {
	mlx_destroy_image(buffer->mlx, buffer->handle);
}

void ib_putp(imbuffer_t *buffer, int x, int y, color_t color) {
	char	*addr;

	addr = buffer->addr;
	addr += x * (buffer->bpp >> 3);
	addr += y * buffer->line_width;
	*((int *) addr) = encode_color(buffer->mlx, color);
}

void ib_flush(window_t *out, const imbuffer_t *buffer) {
	mlx_put_image_to_window(out->mlx, out->handle, buffer->handle, 0, 0);
}
