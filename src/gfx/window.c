#include "gfx.h"
#include <mlx.h>
#include "util/assert.h"
#include "util/syscalls.h"
#include "game/game.h"

#define ESC	53
#define DESTROY_NOTIFY 17

int win_key(int keycode, window_t *window);
int	win_close(window_t *window);

void win_new(window_t *window, const char *title, int width, int height, void *mlx) {
	window->width = width;
	window->height = height;
	window->mlx = mlx;

	window->handle = mlx_new_window(mlx, width, height, (char *) title);
	ib_new(&window->image, mlx, width, height);
	gf_assert(window->handle);
}

void win_destroy(window_t *window) {
	ib_destroy(&window->image);
	mlx_clear_window(window->mlx, window->handle);
	mlx_destroy_window(window->mlx, window->handle);
}

void win_start(window_t *window, win_update_proc proc) {
	mlx_hook(window->handle, DESTROY_NOTIFY, 0, win_close, 0);
	mlx_key_hook(window->handle, win_key, window);
	mlx_loop_hook(window->mlx, proc, window);
	mlx_loop(window->mlx);
}

void win_update(window_t *window) {
	ib_flush(window, &window->image);
}

void win_setptr(window_t *window, void *ptr) {
	window->usr_ptr = ptr;
}

int win_key(int keycode, window_t *window) {
	if (keycode == ESC)
		win_close(window);
	return (0);
}

int	win_close(window_t *window) {
	game_t *game;

	game = window->usr_ptr;
	game_quit(game);
	exit(EXIT_SUCCESS);
}
