#include "gfx.h"
#include <mlx.h>
#include "util/assert.h"

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
	mlx_loop_hook(window->mlx, proc, window);
	mlx_loop(window->mlx);
}

void win_update(window_t *window) {
	ib_flush(window, &window->image);
}

void win_setptr(window_t *window, void *ptr) {
	window->usr_ptr = ptr;
}
