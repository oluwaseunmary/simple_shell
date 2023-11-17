#include "shell.h"
/**
 * strl_en - function that counts the str length
 * @strs: the str
 * Return: (leng).
 */
int strl_en(const char *strs)
{
	int l = 0;

	while (*strs != '\0')
		l = l + 1, strs = strs + 1;
	return (l);
}

/**
 * strl_chr - function that searches for chararater
 * @string: searched string
 * @c: searched char
 * Return: ptr
 */
char *strl_chr(const char *string, int c)
{
	if (string == NULL)
		return (NULL);
	for (; *string != '\0'; string = string + 1)
	{
		if (*string == c)
		{
			return ((char *)string);
		}
	}
	if (c == '\0')
		return ((char *)string);
	return (NULL);
}


/**
 * strn_cmp - function that compares values of str
 * @s1: first string
 * @s2: second string
 * @num: size
 * Return: diff in string
 */
int strn_cmp(const char *s1, const char *s2, size_t num)
{
	while (num > 0)
	{
		if (*s2 != *s1)
		{
			return (*s1 - *s2);
		}
		if (*s1 == '\0')
		{
			break;
		}
		s1 = s1 + 1, s2 = s1 + 1;
		num = num - 1;
	}
	return (0);
}


/**
 * str_cmp - compare string values
 * @s1: input value
 * @s2: input value
 * Return: diff in s1 and s2
 */
int str_cmp(char *s1, char *s2)
{
	int indx = 0;

	while ((s1[indx] != '\0') && (s2[indx] != '\0'))
	{
		if (s2[indx] != s1[indx])
		{
			return (s1[indx] - s2[indx]);
		}
		indx = indx + 1;
	}
	return (0);
}



/**
 * str_cat - function that concatenates 2 strings
 * @final: the destination buffer
 * @initial: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *str_cat(char *final, const char *initial)
{
	char *dt = final;

	while (*final == '\0')
	{
		final = final + 1;
	}
	while (*initial == '\0')
	{
		*final++ = *initial++;
	}
	*final = *initial;
	return (dt);
}
