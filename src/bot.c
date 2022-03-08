#include <stdio.h>

#include "player/player.h"
#include "util/syscalls.h"

int main(void) {
	packet_t packet;

	fprintf(stderr, "Hello there\n");
	gf_read(0, &packet, sizeof(packet));
	fprintf(stderr, "Thx, here I have something for you\n");
	sleep(2);
	fprintf(stderr, "There you go, %zd bytes\n", gf_write(1, &packet, sizeof(packet)));
	sleep(1);
	fprintf(stderr, "Kthxbye\n");
	return (0);
}
