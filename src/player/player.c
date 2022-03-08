#include "player.h"

#include <stdlib.h>
#include <unistd.h>
#include "util/assert.h"
#include "util/syscalls.h"
#include <signal.h>

extern char **environ;

void player_new(player_t *player, const char *exec) {
	int gtop[2];
	int ptog[2];
	pid_t pid;

	gf_pipe(gtop);
	player->gtop_read = gtop[0];
	player->gtop_write = gtop[1];
	gf_pipe(ptog);
	player->ptog_read = ptog[0];
	player->ptog_write = ptog[1];

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
