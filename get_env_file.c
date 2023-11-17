#include "shell.h"
/**
 * str_dup - function that returns pointer to a newly allocate
 * @st: input string
 * Return: pointer to a newly allocated space in memory
 */
char *str_dup(char *st)
{
	int x = 0;
	int idx = 0;
	char *stg;

	if (st == NULL)
	{
		return (NULL);
	}
	while (st[idx] != '\0')
	{
		idx += 1;
	}
	stg = malloc(sizeof(char) * (idx + 1));
	if (stg == NULL)
	{
		return (NULL);
	}
	for (x = 0; st[x]; x += 1)
	{
		stg[x] = st[x];
	}
	return (stg);
}



/**
 * change_d - function that changes dir
 * @args: arguments
 * Return: 0 on success
 */
int change_d(char *args[])
{
	int rt = 1, ro = 0;

	if (args[1] == NULL)
	{
		write(STDERR_FILENO, "cd: no argments\n", 16);
		return (rt);
	}
	if (chdir(args[1]) != 0)
	{
		char *e_msg = "cd: ";

		write(STDERR_FILENO, e_msg, strl_en(e_msg));

		write(STDERR_FILENO, args[1], strl_en(args[1]));

		write(STDERR_FILENO, ": file doesn't exist\n", 21);

		return (rt);
	}
	return (ro);
}


/**
 * env_print - function to print env
 * Return: 0
 */
int env_print(void)
{
	size_t line;
	char **env = environ;
	int ro = 0;

	while (*env)
	{
		line = strl_en(*env), write(STDOUT_FILENO, *env, line);
		write(STDOUT_FILENO, "\n", 1);
		env = env + 1;
	}
	return (ro);
}


/**
 * _setenv - function that sets env
 * @name: variable name
 * @val: env value
 * @ov: overwriting
 * Return: 0
 */
int _setenv(const char *name, const char *val, int ov)
{
	size_t length_a, length_b, env_len;
	int q = 0;
	char *env_var;

	if (getenv(name) != NULL && ov == 0)
		return (0);
	length_a = strl_en(name);
	length_b = strl_en(val);
	env_len = length_b + length_a + 2;

	env_var = (char *)malloc(env_len);

	if (env_var == NULL)
		return (-1);
	str_cpy(env_var, name), env_var[length_a] = '=';
	str_cpy(env_var + length_a + 1, val);
	if (environ == NULL)
		return (-1);
	while (environ[q] != NULL)
	{
		if (strn_cmp(environ[q], name, length_a) == 0 && environ[q][length_a] == '=')
		{
			break;
		}
		q = q + 1;
	}
	if (environ[q] != NULL)
		free(environ[q]), environ[q] = env_var;
	else
		environ[q] = env_var, environ[q + 1] = NULL;
	return (0);
}



/**
 * get_env - takes an env var and returns str val
 * @name: variable name
 * Return: string value of env
*/
char *get_env(const char *name)
{
	int len;
	int x;
	char *data;

	for (x = 0; environ[x] != NULL; x = x + 1)
	{
		data = strl_chr(environ[x], '=');
		if (data != NULL)
		{
			len = data - environ[x];

			if (strn_cmp(environ[x], name, len) == 0)
				return (data + 1);

		}
	}
	return (NULL);
}
