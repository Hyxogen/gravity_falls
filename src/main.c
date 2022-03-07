#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>

int main(void) {
	screen_t screen;

	scr_new(&screen, 20, 20, 1, term_proc);
	ib_clearb(&screen.buffer, '.');
	printf("\n\n\n");
	_render_hex(&screen.buffer, 10, 10, '#');
	_render_hex(&screen.buffer, 12, 12, '%');
	src_flush(&screen);
	pause();
	return 0;
}
