#ifndef PLAYER_H
#define PLAYER_H

#include <unistd.h>

/**
 * packet types:
 * init: game is executed but not yet started. valx is the time in miliseconds each bot has max for a move
 * start: game has started with an empty board, valx is 1 if the player goes first
 * stop: the game has finished for any reason, valx is 0 if the player lost, 1 if the player won, -1 if it was a draw
 * place:
 * 	if sent from server to player, the other player has placed color valx at coordinates (valy,valz)
 *  if sent from player to server, the player requests the server to place color valx at coordinated (valy,valz)
 * rot:
 * 	if sent from server to player, the other player has rotated the gravity of the board to point to valx (can be 0, 1, 2, 3, 4, 5)
 *  if sent from player to server, the player requests rotate the board to point to valx (can be 0, 1, 2, 3, 4, 5)
 * quit: request the bot processes to cleanup and exit
 */
enum ptype_e {
	pt_init,
	pt_start,
	pt_stop,
	pt_place,
	pt_rot,
	pt_quit,
};

typedef struct player {
	pid_t pid;
	int gtop_write;
	int gtop_read;
	int ptog_write;
	int ptog_read;
	int color_count[2];
}	player_t;

typedef struct packet {
	int type;
	int valx;
	int valy;
	int valz;
}	packet_t;

int player_init(void);

void player_new(player_t *player, const char *exec);
void player_destroy(player_t *player);

int player_get_packet(packet_t *packet, const player_t *player, long timeout);
int player_send_packet(packet_t *packet, const player_t *player);

int player_draw(player_t *player, int out[2]);
int player_add(player_t *player, const int tiles[2]);

size_t packet_decode(packet_t *out, void *packet, size_t size);
void packet_encode(packet_t *out, int type, int valx, int valy, int valz);

#endif
