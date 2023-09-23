#include "shell.h"

/**
 * getenv_info - gets the string array copy of our environ
 * @list: Structure containing potential arguments.
 *
 * Return: Always 0
 */
char **getenv_info(inf_table *list)
{
	if (!list->environ || list->env_state)
	{
		list->environ = sll_tableo_strings(list->env);
		list->env_state = 0;
	}

	return (list->environ);
}

/**
 * rem_env_var - Remove an environment variable
 * @list: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int rem_env_var(inf_table *list, char *var)
{
	sll_table *node = list->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = to_comp(node->st, var);
		if (p && *p == '=')
		{
			list->env_state = delete_node_at_index(&(list->env), i);
			i = 0;
			node = list->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (list->env_state);
}

/**
 * set_new_env - Initialize a new environment variable,
 *             or modify an existing one
 * @list: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_new_env(inf_table *list, char *var, char *value)
{
	char *buf = NULL;
	sll_table *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	cpystr(buf, var);
	_strconcat(buf, "=");
	_strconcat(buf, value);
	node = list->env;
	while (node)
	{
		p = to_comp(node->st, var);
		if (p && *p == '=')
		{
			free(node->st);
			node->st = buf;
			list->env_state = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(list->env), buf, 0);
	free(buf);
	list->env_state = 1;
	return (0);
}
