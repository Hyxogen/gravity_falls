#ifndef GAME_H
#define GAME_H

#include "player/player.h"
#include "map/map.h"

typedef struct game_settings {
	int think_time;
	int board_size;
} game_settings_t;

typedef struct game {
	player_t players[2];
	game_settings_t settings;
	hexagon_t *map;
	int turn;
} game_t;

void game_new(game_t *game, const char *sente_exec, const char *gote_exec);
void game_destroy(game_t *game);

int _game_handle_ppacket(game_t *game, player_t *player, const packet_t *packet, int hand[2]);

void game_start(game_t *game, int sente);
void game_stop(game_t *game, int winner);
void game_tick(game_t *game);

#endif
