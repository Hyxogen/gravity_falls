#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include "util/assert.h"

int main(int argc, char **argv) {
	screen_t screen;
	hexagon_t	*hex;

	(void) argc;
	hex = getgrid(atoi(argv[1]));
	gf_assert(hex != NULL);
	scr_new(&screen, 60, 60, 1, term_proc);
	ib_clearb(&screen.buffer, '.');
	render_map(&screen.buffer, hex);
	// _render_hex(&screen.buffer, 10, 10, '#');
	// _render_hex(&screen.buffer, 12, 12, '%');
	src_flush(&screen);
	pause();
	return 0;
}
