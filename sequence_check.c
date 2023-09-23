#include "shell.h"

/**
 * is_seq - check if current char in buffer is a sequence delimeter
 * @list: the parameter struct
 * @buf: the character buffer
 * @p: current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_seq(inf_table *list, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		list->cmd_buf_type = CLI_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		list->cmd_buf_type = CLI_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		list->cmd_buf_type = CLI_ARGS;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * verify_seq - checks we should continue chaining based on last status
 * @p: address of current position in buf
 * @indx: starting position in buf
 * @len: length of buf
 * @list: the parameter struct
 * @buf: character buffer
 *
 * Return: Void
 */
void verify_seq(inf_table *list, char *buf, size_t *p, size_t indx, size_t len)
{
	size_t j = *p;

	if (list->cmd_buf_type == CLI_AND)
	{
		if (list->status)
		{
			buf[indx] = 0;
			j = len;
		}
	}
	if (list->cmd_buf_type == CLI_OR)
	{
		if (!list->status)
		{
			buf[indx] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * manip_alias - replaces any alias in the tokenized string
 * @list: a parameter of struct
 *
 * Return: 1 if replaced and 0 otherwise
 */
int manip_alias(inf_table *list)
{
	int indx;
	sll_table *node;
	char *p;

	for (indx = 0; indx < 10; indx++)
	{
		node = node_starts_with(list->alias, list->agv[0], '=');
		if (!node)
			return (0);
		free(list->agv[0]);
		p = strchkr(node->st, '=');
		if (!p)
			return (0);
		p = duplstr(p + 1);
		if (!p)
			return (0);
		list->agv[0] = p;
	}
	return (1);
}

/**
 * vard_rep - replaces vars in the tokenized string
 * @list: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vard_rep(inf_table *list)
{
	int indx = 0;
	sll_table *node;

	for (indx = 0; list->agv[indx]; indx++)
	{
		if (list->agv[indx][0] != '$' || !list->agv[indx][1])
			continue;

		if (!_strcmp(list->agv[indx], "$?"))
		{
			rep_str(&(list->agv[indx]),
				duplstr(num_conv(list->status, 10, 0)));
			continue;
		}
		if (!_strcmp(list->agv[indx], "$$"))
		{
			rep_str(&(list->agv[indx]),
				duplstr(num_conv(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(list->env, &list->agv[indx][1], '=');
		if (node)
		{
			rep_str(&(list->agv[indx]),
				duplstr(strchkr(node->st, '=') + 1));
			continue;
		}
		rep_str(&list->agv[indx], duplstr(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @old: address of the old string
 * @new: new string to replace
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
