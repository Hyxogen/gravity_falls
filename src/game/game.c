#include "game.h"

#include <string.h>

void game_new(game_t *game, const char *sente_exec, const char *gote_exec) {
	packet_t init_packet;

	memset(&init_packet, 0, sizeof(init_packet));
	init_packet.type = pt_init;
	player_new(&game->players[0], sente_exec);
	player_new(&game->players[1], gote_exec);

	player_send_packet(&init_packet, &game->players[1]);
	init_packet.valx = 1; /* Indicate that this bot goes first */
	player_send_packet(&init_packet, &game->players[0]);
}

void game_destroy(game_t *game) {
	player_destroy(&game->players[0]);
	player_destroy(&game->players[1]);
}

void game_tick(game_t *game) {
	
}