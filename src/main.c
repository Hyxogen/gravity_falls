#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include "util/assert.h"
#include "gfx/gfx.h"
#include "player/player.h"
#include <mlx.h>

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
	player_t player;
	void *handle;

	player_new(&player, "./bot");
	if (argc != 2)
		return EXIT_FAILURE;
	hex = getgrid(atoi(argv[1]));
	gf_assert(hex);
	win_setptr(&win, hex);
	handle = gfx_init();
	win_new(&win, "New Window", 500, 500, handle);
	win_start(&win, update);
	return EXIT_SUCCESS;
}
