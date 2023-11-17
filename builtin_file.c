#include "shell.h"
/**
 * built_check - for builtin command
 * @args: arg count
 * @d_buff: i/p command
 * Return: 1
 */
int built_check(char *args[], char *d_buff)
{
	/* declaring variable */
	int mem;

	if (str_cmp(args[0], "exit") == 0)
	{
		mem = ((args[1] != NULL) && (args[1][0] != '\0'));
		exit_func(d_buff, mem);
		return (1);
	}
	return (0);
}

/**
 * _atoi - string to integer converter
 * @str: ptr to convert
 * Return: int
 */
int _atoi(char *str)
{
	int zer = 1;
	int unit_check = 0;
	int index = 0;
	unsigned int num = 0;

	while (str[index])
	{
		if (str[index] == 45)
			zer *= -1;
		while (str[index] >= 48 && str[index] <= 57)
		{
			unit_check = 1;
			num = (num * 10) + (str[index] - '0');
			index++;
		}
		if (unit_check == 1)
			break;
		index++;
	}
	num *= zer;
	return (num);
}
