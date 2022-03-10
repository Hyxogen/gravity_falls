#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>
#include <stdlib.h>
#include "util/assert.h"
#include "gfx/gfx.h"
#include "game/player.h"
#include "game/game.h"
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

	(void)argv;
	checkboard(0, 0x0054FFCB, 0x004ADBE0, 0x00FA5E44, 0x00DE3C3C);
	game_new(&game, "./bot", "./bot");
	game.settings.think_time = 500000;
	game.players[0].colors[0] = 0x0054FFCB;
	game.players[0].colors[1] = 0x004ADBE0;
	game.players[0].color_count[0] = 5000;
	game.players[0].color_count[1] = 5000;
	game.players[1].colors[0] = 0x00FA5E44;
	game.players[1].colors[1] = 0x00DE3C3C;
	game.players[1].color_count[0] = 5000;
	game.players[1].color_count[1] = 5000;
	player_init();
	len = atoi(argv[1]);
	if (argc != 2)
		return EXIT_FAILURE;
	game.map = gridcreate(len);
	gf_assert(game.map);
	win_setptr(&win, &game);
	handle = gfx_init();
	win_new(&win, "Gravity Falls", (len * 2) * HEXAGON_SIZE, (len * 2) * HEXAGON_SIZE + (len * 2) * 2 * HEXAGON_WIDTH, handle);
	game_start(&game, 0);
	win_start(&win, update);
	return EXIT_SUCCESS;
}
