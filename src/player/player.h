#ifndef PLAYER_H
#define PLAYER_H

#include <unistd.h>

typedef struct player {
	pid_t pid;
	int gtop_write;
	int gtop_read;
	int ptog_write;
	int ptog_read;
}	player_t;

typedef struct packet {
	int type;
	int valx;
	int valy;
	int valz;
}	packet_t;

void player_new(player_t *player, const char *exec);
void player_destroy(player_t *player);

size_t packet_decode(packet_t *out, void *packet, size_t size);
void packet_encode(packet_t *out, int type, int valx, int valy, int valz);

#endif