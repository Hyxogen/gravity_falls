#include "gfx.h"

#include "util/memory.h"
#include <stdlib.h>
#include <string.h>

void ib_new(imbuffer_t *buffer, int width, int height, int bpp) {
	buffer->buffer = gf_safe_malloc(bpp * width * height);
	buffer->width = width;
	buffer->height = height;
	buffer->bpp = bpp;
}

void ib_destroy(imbuffer_t *buffer) {
	free(buffer->buffer);
}

void ib_put(imbuffer_t *buffer, int x, int y, void *val, size_t size) {
	memcpy(buffer->buffer + x + y * buffer->width, val, size);
}

void ib_putb(imbuffer_t *buffer, int x, int y, unsigned char val) {
	buffer->buffer[x + y * buffer->width] = val;
}

void ib_clear(imbuffer_t *buffer) {
	ib_clearb(buffer, 0);
}

void ib_clearb(imbuffer_t *buffer, unsigned char val) {
	memset(buffer->buffer, val, buffer->width * buffer->height * buffer->bpp);
}
