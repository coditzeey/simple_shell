#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(inf_table *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * charsduplic_ate - duplicates characters
 * @ptstri: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *charsduplic_ate(char *ptstri, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (ptstri[i] != ':')
			buf[k++] = ptstri[i];
	buf[k] = 0;
	return (buf);
}

/**
 * func_find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @ptstri: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *func_find_path(inf_table *info, char *ptstri, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!ptstri)
		return (NULL);
	if ((_strlen(cmd) > 2) && to_comp(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!ptstri[i] || ptstri[i] == ':')
		{
			path = charsduplic_ate(ptstri, curr_pos, i);
			if (!*path)
				_strconcat(path, cmd);
			else
			{
				_strconcat(path, "/");
				_strconcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!ptstri[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
