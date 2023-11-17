#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

#define MAX_ARGS 1024

int main(void);
char *pathfinder(char *arg);
int getBuiltin(char *cmd, char *args[]);

#endif
