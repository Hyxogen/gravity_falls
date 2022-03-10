#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include "util/assert.h"
#include "gfx/gfx.h"
#include "game/player.h"
#include "game/game.h"
#include "map/opt.h"
#include <mlx.h>

#define HEXAGON_SIZE 20
#define HEXAGON_WIDTH 2

int update(void *param) {
	window_t *win;
	game_t *game;

	win = param;
	game = win->usr_ptr;
	ib_clear(&win->image, COLOR_WHITE);
	// render_map(&win->image, win->width / 2, HEXAGON_SIZE, HEXAGON_SIZE, 1, game->map, COLOR_RED);
	game_tick(game);
	render_map(&win->image, win->width / 2, HEXAGON_SIZE, HEXAGON_SIZE, HEXAGON_WIDTH, game->map, COLOR_BLACK);
	win_update(win);
	return 0;
}

int main(int argc, char **argv) {
	window_t win;
	game_t game;
	void *handle;
	int len;

	opt_init(argc, argv);
	game_new(&game, getbot(argc, argv), getbot(argc, argv));
	game.settings.think_time = 500000;
	game.settings.tiles = gettiles(argc, argv);
	game.players[0].colors[0] = getcolor(argc, argv);
	game.players[0].colors[1] = getcolor(argc, argv);
	game.players[0].color_count[0] = game.settings.tiles;
	game.players[0].color_count[1] = game.settings.tiles;
	game.players[1].colors[0] = getcolor(argc, argv);
	game.players[1].colors[1] = getcolor(argc, argv);
	game.players[1].color_count[0] = game.settings.tiles;
	game.players[1].color_count[1] = game.settings.tiles;
	player_init();
	len = getsize(argc, argv);
	game.map = gridcreate(len);
	gf_assert(game.map);
	win_setptr(&win, &game);
	handle = gfx_init();
	win_new(&win, "Gravity Falls", (len * 2) * HEXAGON_SIZE, (len * 2) * HEXAGON_SIZE + (len * 2) * 2 * HEXAGON_WIDTH, handle);
	game_start(&game, 0);
	win_start(&win, update);
	return EXIT_SUCCESS;
}
