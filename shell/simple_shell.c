#include "shell.h"
int main(void);
/**
 * main - The entry point of the shell program
 * @argc: Argument count
 * @argv: argument vector
 * @env: environment argument
 * @void: takes no parameter
 *
 * Return: 0
 */

int main(void)
{
	char *prompt = "CMD$ ";
	char *buffer = NULL;
	size_t input = 0;
	size_t len = strlen(prompt);
	ssize_t charreader;
	int wstatus(void);
	int value, q = 0;
	const char *delimeter = " ";
	pid_t processid;
	char *arg;
	char *new_args[1024];
	int Dbuiltin;
	int freeBuffer = 0;

	while (true)
	{
		if (isatty(0))
		{
			write(fileno(stdout), prompt, len);
		}
		charreader = getline(&buffer, &input, stdin);
		if (charreader == -1)
		{
			perror("Error reading input, Exiting Shell...");
			free(buffer);
			exit(0);
		}
		if (buffer[charreader - 1] == '\n')
			buffer[charreader - 1] = '\0';

		q = 0;

		arg = strtok(buffer, delimeter);
		while (arg != NULL)
		{
			new_args[q++] = arg;
			arg = strtok(NULL, delimeter);
		}
		new_args[q] = NULL;
		if (q > 0)
		{
		if (strcmp(new_args[0], "exit") == 0)
		{
			if (freeBuffer)
			{
			free(buffer);
			}
			exit(0);
		}
		Dbuiltin = getBuiltin(new_args[0], new_args);

		if (!Dbuiltin)
		{

					char *pathexec = pathfinder(new_args[0]);
					if (pathexec == NULL)
					{
						perror("Error in Path");
					}
					processid = fork();
					if (processid == -1)
					{
						perror("Forking unsuccessful");
						freeBuffer = 1;
						free(buffer);
						free(pathexec);
						return (-1);
					}
					if (processid == 0)
					{
						value = execve(pathexec, new_args, NULL);
						if (value == -1)
						{
							perror("Error in execution");
							free(buffer);
							free(pathexec);
							exit(1);
						}
					}
				}
			}
			else
			{
				wait(NULL);
			}

			free(pathexec);
		}
		}
		if (freeBuffer)
		{
		free(buffer);
		freeBuffer = 0;
		}
	}
	return (0);

}
