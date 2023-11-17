#include "shell.h"
/**
 * _strtok - Function that divides words
 * @s: the string to divide
 * @del: the token to check
 * Return: pointer
 */
char *_strtok(char *s, const char *del)
{
	/* declaring and initializing variables */
	static char *l_tok = '\0';
	char *tok;

	if (s != NULL)
		l_tok = s;
	if (l_tok == NULL)
		return (NULL);
	tok = l_tok;
	for (tok = l_tok; *l_tok != '\0'; l_tok++)
	{
		if (strl_chr(del, *l_tok) != NULL)
		{
			*l_tok = '\0', l_tok += 1;
			return (tok);
		}
	}
	if (*tok == '\0')
	{
		l_tok = NULL;
		return (NULL);
	}
	return (tok);
}
