#include "player.h"

#include <stdlib.h>
#include <unistd.h>
#include "util/assert.h"

void player_new(player_t *player, const char *exec) {
	pid_t pid;

	pid = fork();
	gf_assert(pid != -1);
	if (pid == 0) {
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	} else
		player->pid = pid;
}

void player_destroy(player_t *player) {

}