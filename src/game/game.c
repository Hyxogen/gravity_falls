#include "game.h"

#include <string.h>

void game_new(game_t *game, const char *sente_exec, const char *gote_exec) {
	packet_t init_packet;

	memset(game, 0, sizeof(*game));
	memset(&init_packet, 0, sizeof(init_packet));
	init_packet.type = pt_init;
	player_new(&game->players[0], sente_exec);
	player_new(&game->players[1], gote_exec);

	player_send_packet(&init_packet, &game->players[0]);
	player_send_packet(&init_packet, &game->players[1]);
}

void game_start(game_t *game, int sente) {
	packet_t start_packet;

	memset(&start_packet, 0, sizeof(start_packet));
	start_packet.type = pt_start;
	start_packet.valx = game->settings.think_time;
	start_packet.valy = game->settings.board_size;
	start_packet.valz = sente == 0; /* Indicate that this bot goes first */
	player_send_packet(&start_packet, &game->players[0]);
	start_packet.valz = !sente; /* Indicate that this bot goes first */
	player_send_packet(&start_packet, &game->players[1]);
	game->turn = sente;
}

void game_stop(game_t *game, int winner) {
	packet_t stop_packet;

	game->turn = -1;
	memset(&stop_packet, 0, sizeof(stop_packet));
	stop_packet.type = pt_stop;
	stop_packet.valx = winner == -1 ? -1 : winner == 0;
	player_send_packet(&stop_packet, &game->players[0]);
	stop_packet.valx = winner == -1 ? -1 : winner == 1;
	player_send_packet(&stop_packet, &game->players[1]);
}

void game_destroy(game_t *game) {
	player_destroy(&game->players[0]);
	player_destroy(&game->players[1]);
}

int _game_handle_ppacket(game_t *game, const packet_t *packet) {
	switch (packet->type) {
		case pt_place:
			return droptile(game->map, packet->valy, packet->valx);
		case pt_rot:
			return gridrotate(game->map, (unsigned int) packet->valx);
		default:
			return -1;
	}
}

void game_tick(game_t *game) {
	packet_t move;
	int rc;

	if (game->turn == -1)
		return;
	if (player_get_packet(&move, &game->players[game->turn], game->settings.think_time) < 0) {
		fprintf(stdout, "no move\n");
		game_stop(game, !game->turn);
		return;
	}
	rc = _game_handle_ppacket(game, &move);
	switch (rc) {
		case 1:
			fprintf(stdout, "someone won\n");
			game_stop(game, -1); /* TODO set correct winner */
			return;
		case 2:
		case 3:
			fprintf(stdout, "draw\n");
			game_stop(game, -1);
			return;
		case 4:
		case 5:
			fprintf(stdout, "illegal move\n");
			game_stop(game, !game->turn);
			return;
	}
	game->turn = !game->turn;
}