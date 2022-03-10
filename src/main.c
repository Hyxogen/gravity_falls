#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include "util/assert.h"
#include "gfx/gfx.h"
#include "player/player.h"
#include "game/game.h"
#include <mlx.h>

int update(void *param) {
	window_t *win;
	game_t *game;

	win = param;
	game = win->usr_ptr;
	render_map(&win->image, 250, 50, 50, 1, game->map, COLOR_RED);
	game_tick(game);
	render_map(&win->image, 250, 50, 50, 1, game->map, COLOR_RED);
	win_update(win);
	return 0;
}

int main(int argc, char **argv) {
	window_t win;
	game_t game;
	void *handle;

	(void)argv;
	game_new(&game, "./bot", "./bot");
	player_init();
	if (argc != 2)
		return EXIT_FAILURE;
	game.map = getgrid(atoi(argv[1]));
	gf_assert(game.map);
	win_setptr(&win, &game);
	handle = gfx_init();
	win_new(&win, "New Window", 500, 500, handle);
	win_start(&win, update);
	return EXIT_SUCCESS;
}
