#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite);
int _setenv2(const char *n, const char *v, int ov);
int env_print(void);

char *str_cpy(char *final, const char *initial);
int _atoi(char *s);
int change_d(char *args[]);

ssize_t get_cmd(char **cmd_store, size_t *cmd_size);
int child_pro(char *av[]);
int parent_pro(pid_t pid);

int cmd_ex(char *cmd_store);
void mem_clear(char *cmd_store);
int args_preps(char *d_buff, char **args);

int strl_en(const char *strs);
char *find_exec(char *d_buff);
ssize_t _getline(char **lineptr, size_t *n, int file_des);

char *strl_chr(const char *string, int c);
int built_check(char *args[], char *d_buff);
void exit_func(char *d_buff, int buff_store);

char *_strtok(char *s, const char *del);
int str_cmp(char *s1, char *s2);
char *exec_c(char *d_buff);

char *locate_cmd(char *cmd, char *path);
int strn_cmp(const char *s1, const char *s2, size_t num);
char *str_cat(char *final, const char *initial);

char *str_dup(char *st);
char *get_env(const char *name);

#endif
