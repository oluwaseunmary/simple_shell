#include "shell.h"

/**
 * pathfinder - function that locates the path
 * @arg: argument
 *
 * Return: NULL if not found, otherwise the path
 */
char *pathfinder(char *arg)
{
	char *path = getenv("PATH");

	if (path == NULL)
		return (NULL);

	char *pathdup = strdup(path);

	if (pathdup == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	const char *delim = ":";
	char *dir = strtok(pathdup, delim);
	struct stat buffer;

	while (dir)
	{
		size_t cmdLen = strlen(arg);
		size_t dirLen = strlen(dir);
		char *pathcheck = (char *)malloc(cmdLen + dirLen + 2);

		if (pathcheck)
		{
			strcpy(pathcheck, dir);
			strcat(pathcheck, "/");
			strcat(pathcheck, arg);

			if (stat(pathcheck, &buffer) == 0 && S_ISREG(buffer.st_mode)
					&& (buffer.st_mode & S_IXUSR))
			{
				free(pathdup);
				return (pathcheck);
			}
			free(pathcheck);
		}
		dir = strtok(NULL, delim);
	}
	free(pathdup);
	return (NULL);
}
