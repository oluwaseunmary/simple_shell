#include "shell.h"
/**
 * locate_cmd - locate the cmd line
 * @cmd: variable name
 * @path: path
 * Return: env str
*/
char *locate_cmd(char *cmd, char *path)
{
	char *tkn;
	char *tmp, *dlim = ":", *exec_cmd = NULL;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0 && !access(cmd, F_OK))
			return (str_dup(cmd));
		else
			return (NULL);
	}
	tkn = strtok(path, dlim);
	while (tkn != NULL)
	{
		if (cmd[0] == '/')
			tmp = malloc(strl_en(tkn) + strl_en(cmd) + 1);
		else
			tmp = malloc(strl_en(tkn) + strl_en(cmd) + 2);
		if (tmp == NULL)
		{
			perror("Allocating memory failed!");
			return (NULL);
		}
		if (cmd[0] == '/')
			str_cpy(tmp, tkn);
		else
			str_cpy(tmp, tkn), str_cat(tmp, "/"), str_cat(tmp, cmd);
		if (access(tmp, X_OK) == 0 && !access(tmp, F_OK))
		{
			exec_cmd = tmp;
			break;
		}
		free(tmp);
		tkn = strtok(NULL, dlim);
	}
	return (exec_cmd);
}



/**
 * child_pro - executes the child process
 * @av: pointer to the argument count
 * Return: 0 if successful
 */
int child_pro(char *av[])
{
	char *run_cmd;
	int exec;

	run_cmd = exec_c(av[0]);

	if (run_cmd == NULL)
	{
		perror("Executable not found.\n");
		return (-1);
	}
	exec = execve(run_cmd, av, environ);
	if (exec == -1)
	{
		perror("Execve failed");
		return (-1);
	}
	return (0);
}


/**
 * parent_pro - function to keep parent process on hold until child execute
 * @pid: the child process id
 * Return: 0 if successful, -1 otherwise
 */

int parent_pro(pid_t pid)
{
	int update;
	int delay = waitpid(pid, &update, 0);

	if (delay == -1)
	{
		perror("waitpid failed");
		return (-1);
	}
	return (0);
}
