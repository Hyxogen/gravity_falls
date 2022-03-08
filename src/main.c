#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include "util/assert.h"
#include "gfx/gfx.h"
#include <mlx.h>

/*
int main(int argc, char **argv) {
	window_t win;
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
*/

int update(void *param) {
	window_t *win;
	hexagon_t *hex;

	win = param;
	hex = win->usr_ptr;
	// win_putp(win, 250, 250, COLOR_RED);
	// render_hexh(&win->image, 250, 250, 100, 1, COLOR_RED);
	// render_hexf(&win->image, 250, 250, 95, COLOR_BLUE);
	render_map(&win->image, 250, 50, 50, 1, hex, COLOR_RED);
	win_update(win);
	return 0;
}

int main(int argc, char **argv) {
	hexagon_t *hex;
	window_t win;
	void *handle;

	if (argc != 2)
		return EXIT_FAILURE;
	hex = getgrid(atoi(argv[1]));
	droptile(hex, 0, COLOR_GREEN);
	droptile(hex, 0, COLOR_RED);
	droptile(hex, 0, COLOR_RED);
	droptile(hex, 0, COLOR_RED);
	droptile(hex, 0, COLOR_RED);
	droptile(hex, 0, COLOR_RED);
	gf_assert(hex);
	win_setptr(&win, hex);
	handle = gfx_init();
	win_new(&win, "New Window", 500, 500, handle);
	win_start(&win, update);
	return EXIT_SUCCESS;
}
