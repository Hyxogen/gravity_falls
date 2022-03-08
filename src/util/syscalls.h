#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <unistd.h>

int gf_fork(void);
int gf_dup2(int fildes, int fildes2);
int gf_execve(const char *path, char *const argv[], char *const envp[]);
int gf_close(int filedes);
int gf_kill(pid_t pid, int sig);

#endif
