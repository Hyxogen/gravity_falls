#include <stdio.h>

#include "player/player.h"
#include "util/syscalls.h"
#include "gfx/gfx.h"
#include <string.h>
#include <stdlib.h>

int main(void) {
	packet_t packet;
	packet_t in;

	memset(&packet, 0, sizeof(packet));
	while (1) {
		gf_read(0, &in, sizeof(in));
		if (in.type != pt_draw)
			continue;
		if (random() & 1) {
			packet.type = pt_place;
			packet.valy = random() % 18 - 9; 
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
		gf_write(1, &packet, sizeof(packet));
	}
	return (0);
}
