#include "shell.h"
int main(int argc, char **argv, char **env);
/**
 * main - The entry point of the shell program
 * @argc: Argument count
 * @env: The current environment
 * @argv: Argument vector
 *
 * Return: 0
 */

int main(int argc, char **argv, char **env)
{
	(void) argc;
	char *prompt = "CMD$ ";
	char *buffer = NULL;
	size_t input = 0;
	size_t len = strlen(prompt);
	ssize_t charreader;
	int wstatus;
	int value, i = 0;
	const char *delimeter = " ";
	char *arg;
	pid_t processid;
	char *new_args[1024];

	while (1)
	{
		if (isatty(0))
		{
			write(fileno(stdout), prompt, len);
		}
		charreader = getline(&buffer, &input, stdin);
		if (charreader == -1)
		{
			perror("Exiting Shell...");
			free(buffer);
			exit(0);
		}
		if (buffer[charreader - 1] == '\n')
			buffer[charreader - 1] = '\0';

		i = 0;

		arg = strtok(buffer, delimeter);
		while (arg != NULL)
		{
			new_args[i] = arg;
			arg = strtok(NULL, delimeter);
			i++;
		}
		new_args[i] = NULL;
		if (strcmp(new_args[0], "exit") == 0)
		{
			free(buffer);
			exit(0);
		}
		int Dbuiltin = getBuiltin(new_args[0], new_args);

		if (!Dbuiltin)
		{
			char *pathexec = pathfinder(new_args[0]);

			if (pathexec == NULL)
			{
				perror("Error in Path");
				continue;
			}
			processid = fork();
			if (processid == -1)
			{
				perror("Forking unsuccessful");
				free(buffer);
				return (-1);
			}
			if (processid == 0)
			{
				value = execve(pathexec, new_args, NULL);
				if (value == -1)
				{
					perror("Error in Execution, Command not found");
					exit(1);
				}
		}
			else
			{
				wait(&wstatus);
			}
			free(pathexec);
		}
	}
	free(buffer);
	return (0);
}
