#include "player.h"

#include "util/assert.h"
#include "util/syscalls.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>

extern char **environ;

void _player_timeout_handler(int sig, siginfo_t *info, void *context) {
	(void) sig;
	(void) info;
	(void) context;
}

int player_init(void) {
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = _player_timeout_handler;
	act.sa_flags = SA_SIGINFO;
	gf_sigaction(SIGALRM, &act, NULL);
	return 0;
}

int player_get_packet(packet_t *packet, const player_t *player, long timeout) {
	struct itimerval val;
	ssize_t ret;

	memset(&val, 0, sizeof(val));
	val.it_value.tv_sec = timeout / 1000;
	val.it_value.tv_usec = (timeout % 1000) * 1000;
	gf_setitimer(ITIMER_REAL, &val, NULL);
	ret = gf_read(player->ptog_read, packet, sizeof(*packet));
	if (ret < 0 || (size_t) ret < sizeof(*packet))
		return -1;
	return 0;
}

int player_send_packet(packet_t *packet, const player_t *player) {
	gf_write(player->gtop_write, packet, sizeof(*packet));
	return 0;
}

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

int player_draw(player_t *player, int out[2]) {
	long ran;

	while ((ran = random()) == 0)
		continue;
	return (0):
}

int player_add(player_t *player, const int tiles[2]) {

}

void player_destroy(player_t *player) {
	gf_close(player->gtop_write);
	gf_close(player->ptog_read);
	gf_kill(player->pid, SIGKILL);
}
