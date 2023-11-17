#include "shell.h"
char *pathfinder(char *arg);
/**
 * pathfinder - function that locates the path
 * @arg: argument
 *
 * Return: NULL
 */

char *pathfinder(char *arg)
{
	char *path = getenv("PATH");
	char *pathdup = strdup(path);
	char *delim = ":";
	char *dir = strtok(pathdup, delim);

	struct stat buffer;

	if (path == NULL)
	{
		perror("Error getting path");
		return(NULL);
	}
	pathdup = strdup(path);
	if (pathdup == NULL)
	{
		perror("Error duplicating Path");
		return(NULL);
	}
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
