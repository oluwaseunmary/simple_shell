#include "shell.h"

/**
 * exec_c - function that find exec cmd
 * @d_buff: cmd i/p
 * Return: Ptr
 */
char *exec_c(char *d_buff)
{
	char *lim = " ";

	return (strtok(d_buff, lim));
}


/**
 * args_preps - function that sets the cmd args
 * @d_buff: cmd i/p
 * @args: cmd arguments
 * Return: 0
 */
int args_preps(char *d_buff, char **args)
{
	int arg_idx = 0;
	char *dlim = " ", *tkn;
	int end = 0;

	tkn = strtok(d_buff, dlim);
	while (tkn != NULL)
	{
		args[arg_idx++] = tkn, tkn = strtok(NULL, dlim);
		if (arg_idx >= 64 - 1)
		{
			perror("more cmd args than required.\n");
			return (-1);
		}
	}
	args[arg_idx] = NULL;
	return (end);
}

/**
 * get_cmd - function that reads input cmds
 * @cmd_store: storage
 * @cmd_size: storage size
 * Return: ptr
 */
ssize_t get_cmd(char **cmd_store, size_t *cmd_size)
{
	ssize_t cmd = getline(cmd_store, cmd_size, stdin);

	return (cmd);
}
