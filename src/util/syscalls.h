#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <unistd.h>
#include <sys/time.h>

struct sigaction;

int gf_fork(void);
int gf_dup2(int fildes, int fildes2);
int gf_execve(const char *path, char *const argv[], char *const envp[]);
int gf_close(int filedes);
int gf_kill(pid_t pid, int sig);
int gf_pipe(int fildes[2]);
ssize_t gf_read(int fildes, void *buf, size_t nbyte);
ssize_t gf_write(int fildes, const void *buf, size_t nbyte);
int gf_setitimer(int which, const struct itimerval *restrict value, struct itimerval *restrict ovalue);
int gf_sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);

#endif
