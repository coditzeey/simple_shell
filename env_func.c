#include "shell.h"

/**
 * print_curr_env - prints the current environment
 * @list: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_curr_env(inf_table *list)
{
	print_list_str(list->env);
	return (0);
}

/**
 * get_envalue - get the value of environment variable
 * @list: Structure containing potential arguments
 * @nm: env var
 *
 * Return: the value
 */
char *get_envalue(inf_table *list, const char *nm)
{
	sll_table *node = list->env;
	char *p;

	while (node)
	{
		p = to_comp(node->st, nm);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * make_env - Initialize a new environment variable.
 *
 * @list: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int make_env(inf_table *list)
{
	if (list->agc != 3)
	{
		input_printff("check number of arguments\n");
		return (1);
	}
	if (set_new_env(list, list->agv[1], list->agv[2]))
		return (0);
	return (1);
}

/**
 * rem_made_env - Remove an environment variable
 * @list: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int rem_made_env(inf_table *list)
{
	int i;

	if (list->agc == 1)
	{
		input_printff("Too few arguements.\n");
		return (1);
	}

	i = 1;

	while (i <= list->agc)
	{
		rem_env_var(list, list->agv[i]);
		i++;
	}

	return (0);
}

/**
 * add_to_envlist -  add to env linked list
 * @list: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int add_to_envlist(inf_table *list)
{
	sll_table *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		create_node_end(&node, environ[i], 0);
	list->env = node;
	return (0);
}
