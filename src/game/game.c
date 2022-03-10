#include "game.h"

#include "util/syscalls.h"
#include <string.h>

const static char *g_packet_names[] = {
	"packet_init",
	"packet_start",
	"packet_top",
	"packet_draw",
	"packet_place",
	"packet_rot",
	"packet_quit"
};

void game_new(game_t *game, const char *sente_exec, const char *gote_exec) {
	memset(game, 0, sizeof(*game));
	player_new(&game->players[0], sente_exec);
	player_new(&game->players[1], gote_exec);
}

void game_start(game_t *game, int sente, int (*update)()) {
	packet_t start_packet;

	memset(&start_packet, 0, sizeof(start_packet));
	start_packet.type = pt_start;
	start_packet.valx = game->settings.think_time;
	start_packet.valy = game->settings.board_size;
	start_packet.valz = game->settings.tiles;
	player_send_packet(&start_packet, &game->players[0]);
	player_send_packet(&start_packet, &game->players[1]);
	game->turn = sente;
	win_start(&game->window, update);
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
	if (winner != -1)
		fprintf(stdout, "player %d \"%s\" won\n", winner + 1, game->players[winner].exec);
}

int _game_handle_ppacket(game_t *game, player_t *player, const packet_t *packet, int hand[2]) {
	switch (packet->type) {
		case pt_place:
			if (hand[packet->valx] <= 0) {
				printf("played did not have %d (%d,%d)\n", packet->valx, hand[0], hand[1]);
				return -5;
			}
			hand[packet->valx]--;
			player_add(player, hand);
			return droptile(game->map, packet->valy, player->colors[packet->valx]);
		case pt_rot:
			return gridrotate(&game->map, (unsigned int) packet->valx);
		default:
			return -5;
	}
}

void game_tick(game_t *game) {
	packet_t move;
	player_t *player;
	int hand[2];
	int rc;

	hand[0] = 0;
	hand[1] = 0;
	if (game->turn == -1)
	{
		game_quit(game);
		return;
	}
	player = &game->players[game->turn];
	if (player_draw(player, hand) == 0) {
		game_stop(game, !game->turn);
		return;
	}
	player_send_hand(player, hand);
	if (player_get_packet(&move, player, game->settings.think_time) < 0) {
		fprintf(stdout, "Player %d: Timeout\n", game->turn + 1);
		game_stop(game, !game->turn);
		return;
	}
	rc = _game_handle_ppacket(game, player, &move, hand);
	switch (rc) {
		case -1:
			fprintf(stdout, "Draw: both players won\n");
			game_stop(game, -1); 
			return;
		case -2:
			fprintf(stdout, "Draw: full field\n");
			game_stop(game, -1); 
			return;
		case -3:
			fprintf(stdout, "Player %d: Illegal move: column is already full\n", game->turn + 1);
			game_stop(game, !game->turn);
			return;
		case -4:
			fprintf(stdout, "Player %d: Illegal move: Tile dropped outside of field\n", game->turn + 1);
			game_stop(game, !game->turn);
			return;
		case -5:
			game_stop(game, !game->turn);
			return;
		case 0:
			player_send_packet(&move, &game->players[!game->turn]);
			break;
		default:
			if (player->colors[0] == rc || player->colors[1] == rc)
				game_stop(game, game->turn);
			else
				game_stop(game, !game->turn);
			return;
	}
	game->turn = !game->turn;
}

void game_quit(game_t *game) {
	player_destroy(&game->players[0]);
	player_destroy(&game->players[1]);
	griddestroy(game->map);
	exit(EXIT_SUCCESS);
}

void game_packet_print(game_t *game, const packet_t *packet) {
	(void) game;
	fprintf(stderr, "{ type:\"%s\", valx:%d, valy:%d, valz:%d }\n", g_packet_names[packet->type], packet->valx, packet->valy, packet->valz);
}
