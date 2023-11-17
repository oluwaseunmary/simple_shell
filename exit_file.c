#include "shell.h"
/**
 * cmd_ex - execute commands
 * @cmd_store: input command
 * Return: calling process pid
 */

int cmd_ex(char *cmd_store)
{
	int output;
	char *args[64];
	char *exec_cmd;
	pid_t pid;

	if (args_preps(cmd_store, args) == -1)
		return (-1);
	if (str_cmp(args[0], "env") == 0)
		return (env_print());
	if (str_cmp(args[0], "cd") == 0)
		return (change_d(args));
	if (built_check(args, cmd_store))
		return (0);

	exec_cmd = locate_cmd(args[0], getenv("PATH"));
	if (exec_cmd == NULL)
	{
		perror("cmd not found.\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed"), free(exec_cmd);
		return (-1);
	} else if (pid == 0)
	{
		output = child_pro(args), free(exec_cmd);
		return (output);
	}
	else
	{
		free(exec_cmd);
		return (parent_pro(pid));
	}
}




/**
 * mem_clear - cleans up the memory allocated
 * @cmd_store: the memory to free
 * Return: nothing
 */

void mem_clear(char *cmd_store)
{
	free(cmd_store);
}


/**
 * exit_func - exit a process
 * @d_buff: the command entered
 * @buff_store: stores the command
 * Return: nothing
 */

void exit_func(char *d_buff, int buff_store)
{
	char e_msg[20];

	mem_clear(d_buff);

	if (d_buff != NULL && d_buff[0] != '\0')
	{
		buff_store = _atoi(d_buff);

		if ((d_buff[0] != '0') && (buff_store == 0))
		{
			str_cpy(e_msg, "Exit with error: ");

			write(STDERR_FILENO, e_msg, sizeof(e_msg) - 1);

			write(STDERR_FILENO, d_buff, strl_en(d_buff));

			write(STDERR_FILENO, "\n", 1);

			exit(1);
		}
		exit(buff_store);
	}
	exit(0);
}

/**
 * str_cpy - Copy a string
 * @final: final value
 * @initial: Source
 * Return: the pointer to dest
 */
char *str_cpy(char *final, const char *initial)
{
	int idx;

	for (idx = 0; initial[idx] != '\0'; idx += 1)
		final[idx] = initial[idx];
	final[idx += 1] = '\0';
	return (final);
}
