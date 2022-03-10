#include <stdio.h>

#include "game/player.h"
#include "game/game.h"
#include "util/syscalls.h"
#include "gfx/gfx.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

int main(void) {
	packet_t packet;
	packet_t in;
	int columns;

	srandomdev();
	memset(&packet, 0, sizeof(packet));
	columns = INT_MAX;
	while (1) {
		gf_read(0, &in, sizeof(in));
		if (in.type == pt_start) {
			columns = in.valy;
			continue;
		} else if (in.type == pt_quit) {
			break;
		} else if (in.type != pt_draw)
			continue;
		if (random() & 1) {
			packet.type = pt_place;
			packet.valy = random() % (columns - 2) - ((columns / 2) - 1); 
			if (in.valx == 0)
				packet.valx = 1;
			else if (in.valy == 0)
				packet.valx = 0;
			else
				packet.valx = random() & 1;
		} else {
			packet.type = pt_rot;
			packet.valx = random();
		}
		sleep(1);
		gf_write(1, &packet, sizeof(packet));
	}
	return (0);
}
