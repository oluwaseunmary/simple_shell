#include "shell.h"
/**
 * getBuiltin - execute the built-in commands in shell program
 * @cmd: argument to store the command input
 * @args: array of arguments to store main user input
 *
 * Return: -1 when unsucessful
 */
int getBuiltin(char *cmd, char *args[])
{
	if (strcmp(cmd, "cd") == 0)
	{
		if (args[1])
		{
			if (chdir(args[1]) == -1)
			{
				perror("cd");
			}
		}
		return (1);
	}
	if (strcmp(cmd, "exit") == 0)
	{
		if (args[1])
		{
			exit(atoi(args[1]));
		}
		exit(0);
	}
	return (0);
}
