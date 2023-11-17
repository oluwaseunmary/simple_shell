#include "shell.h"

/**
 * main - entry point
 * @arc: args count
 * @arv: arg vectors count
 * Return: 0
 */

int main(int arc, char *arv[])
{
	int output;
	char *prom = "$ ", *buf_cmd = NULL;
	ssize_t cmd;
	size_t buf_siz = 0;

	setenv("PATH", "/bin:/usr/bin:/usr/local/bin", 1);
	if (arc > 1)
		return (cmd_ex(arv[1]));
	while (true)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, prom, 2), cmd = get_cmd(&buf_cmd, &buf_siz);
		} else
		{
			if (getline(&buf_cmd, &buf_siz, stdin) == -1)
				break;
			cmd = strl_en(buf_cmd);
		}
		if (cmd == (ssize_t)-1)
		{
			perror("Error in read line"), mem_clear(buf_cmd);
			return (-1);
		}
		if (buf_cmd[cmd - 1] == '\n')
			buf_cmd[cmd - 1] = '\0';
		if (str_cmp(buf_cmd, "exit") == 0)
		{
			mem_clear(buf_cmd);
			return (0);
		}
		output = cmd_ex(buf_cmd);
		if (output == -1)
		{
			mem_clear(buf_cmd);
			return (0);
		}}
	mem_clear(buf_cmd);
	return (0);
}
