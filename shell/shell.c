#include "shell.h"
int main(void);
/**
 * main - function that hold shell.
 * @void:
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
	pid_t processid;
	int wstatus;
	int value, q = 0;
	const char *delimeter = " ";
	char *new_args[1024];
	char *arg;
	
	while (1)
	{
		write(fileno(stdout), prompt, len);
		
		charreader = getline(&buffer, &input, stdin);
		if (charreader == -1)
		{
			perror("Exiting Shell...");
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
		processid = fork();
		if (processid == -1)
		{
			perror("Forking unsuccessful");
			free(buffer);
			return (-1);
		}
		if (processid == 0)
		{
			value = execvp(new_args[0], new_args);
			if (value == -1)
			{
				perror("Error in Execution");
				exit(1);
			}
		}
		else
		{
			wait(&wstatus);
		}
	}
	free(buffer);
	return (0);
}
