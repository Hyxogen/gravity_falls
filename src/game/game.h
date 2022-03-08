#ifndef GAME_H
#define GAME_H

#include "player/player.h"

typedef struct game {
	player_t players[2];
	int turn;
}	game_t;

void game_new(game_t *game, const char *sente_exec, const char *gote_exec);
void game_destroy(game_t *game);

void game_tick(game_t *game);

#endif