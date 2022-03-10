#include <stdio.h>

#include "player/player.h"
#include "util/syscalls.h"
#include "gfx/gfx.h"
#include <string.h>

int main(void) {
	packet_t packet;

	memset(&packet, 0, sizeof(packet));
	packet.type = pt_place;
	packet.valx = COLOR_RED;
	packet.valy = 0;
	sleep(4);
	while (1) {
		gf_write(1, &packet, sizeof(packet));
		sleep(1);
	}
	return (0);
}
