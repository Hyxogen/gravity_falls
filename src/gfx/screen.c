#include "gfx.h"

#include <stdio.h>

void term_proc(const imbuffer_t *buffer, void *usr_ptr) {
	int x, y;
	int width, height;

	(void)usr_ptr;
	width = buffer->width;
	height = buffer->height;
	scr_clear(NULL);
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++)
			printf("%c", buffer->buffer[x + y * width]);
		printf("\n");
	}
}

void scr_new(screen_t *scr, int width, int height, int bpp, scr_flush_proc proc) {
	ib_new(&scr->buffer, width, height, bpp);
	scr->flush_proc = proc;
}

void src_flush(const screen_t *scr) {
	scr->flush_proc(&scr->buffer, scr->usr_ptr);
}

void scr_clear(const screen_t *src) {
	(void) src;
	printf("\x1b[2J\x1b[1;1H");
}
