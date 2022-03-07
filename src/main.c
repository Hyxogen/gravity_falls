#include <stdio.h>
#include "gfx/gfx.h"
#include <unistd.h>

int main(void) {
	screen_t screen;

	scr_new(&screen, 10, 10, 1, term_proc);
	ib_clearb(&screen.buffer, '@');
	ib_putb(&screen.buffer, 2, 2, 'a');
	src_flush(&screen);
	while (1) {
		scr_clear(NULL);
		printf("a\n");
		sleep(1);
	}
	return 0;
}
