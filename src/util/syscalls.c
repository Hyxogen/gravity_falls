#include "syscalls.h"

#include "assert.h"
#include <signal.h>
#include <errno.h>
#include <string.h>

int gf_fork(void) {
	int ret;

	ret = fork();
	if (ret == -1)
		gf_abort("fork failed: error:\"%s\"\n", strerror(errno));
	return ret;
}

int gf_dup2(int fildes, int fildes2) {
	int ret;

	ret = dup2(fildes, fildes2);
	if (ret <= -1)
		gf_abort("dup2 failed: error:\"%s\"\n", strerror(errno));
	return ret;
}

int gf_execve(const char *path, char *const argv[], char *const envp[]) {
	int ret;

	ret = execve(path, argv, envp);
	if (ret)
		gf_abort("execve failed: error:\"%s\"\n", strerror(errno));
	return -1; /* This will never happen */
}

int gf_close(int filedes) {
	int ret;

	ret = close(filedes);
	if (ret <= -1)
		gf_abort("close failed: error:\"%s\"\n", strerror(errno));
	return ret;
}

int gf_kill(pid_t pid, int sig) {
	int ret;

	ret = kill(pid, sig);
	if (ret <= -1)
		gf_abort("kill failed: error:\"%s\"\n", strerror(errno));
	return ret;
}
