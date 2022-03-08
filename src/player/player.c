#include "player.h"

#include <stdlib.h>
#include <unistd.h>
#include "util/assert.h"
#include "util/syscalls.h"
#include <signal.h>

extern char **environ;

void player_new(player_t *player, const char *exec) {
	pid_t pid;

	pid = gf_fork();
	if (pid == 0) {
		gf_close(STDIN_FILENO);
		gf_close(STDOUT_FILENO);
		gf_dup2(player->gtop_read, STDIN_FILENO);
		gf_dup2(player->ptog_write, STDOUT_FILENO);
		gf_execve(exec, NULL, environ);
	} else
		player->pid = pid;
}

void player_destroy(player_t *player) {
	gf_close(player->gtop_write);
	gf_close(player->ptog_read);
	gf_kill(player->pid, SIGKILL);
}
