#include "shell.h"
/**
 * _getline - reads the line
 * @lineptr: a pointer
 * @n: pointer to the number
 * @file_des: file descriptor
 * Return: the number
 */

ssize_t _getline(char **lineptr, size_t *n, int file_des)
{
	static char buffer[128];
	static size_t pos;
	static ssize_t bytes_in_buffer;
	ssize_t bytes_read = 0, line_length = 0;
	char *new_lineptr;

	if (file_des < 0 || !lineptr || !n)
		return (-1);  /* Invalid input parameters */
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128, *lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1); /* failed */
	}
	while (1)
	{
		if (pos >= (size_t)bytes_in_buffer)
		{
			bytes_read = read(file_des, buffer, sizeof(buffer));
			if (bytes_read <= 0)
			{
				if (line_length == 0)
					return (-1);
				break;
			}
			bytes_in_buffer = bytes_read, pos = 0;
		}
		if ((size_t)line_length >= *n)
		{
			*n *= 2, new_lineptr = (char *)realloc(*lineptr, *n);
			if (!new_lineptr)
				return (-1);  /* failed */
			*lineptr = new_lineptr;
		}
		(*lineptr)[line_length++] = buffer[pos++];
		if (buffer[pos - 1] == '\n')
			break;
	}
	(*lineptr)[line_length] = '\0';
	return (line_length);
}
