#include "shell.h"

/**
 * func_history - displays the history list
 *
 * @list: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int func_history(inf_table *list)
{
	print_list(list->history);
	return (0);
}

/**
 * func_rem_alias - sets alias to string
 * @list: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int func_rem_alias(inf_table *list, char *str)
{
	char *p, c;
	int ret;

	p = strchkr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(list->alias),
		get_node_index(list->alias, node_starts_with(list->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * func_make_alias - sets alias to string
 * @list: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int func_make_alias(inf_table *list, char *str)
{
	char *p;

	p = strchkr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (func_rem_alias(list, str));

	func_rem_alias(list, str);
	return (add_node_end(&(list->alias), str, 0) == NULL);
}

/**
 * alias_printf - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_printf(sll_table *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchkr(node->st, '=');
		for (a = node->st; a <= p; a++)
			charprint(*a);
		charprint('\'');
		strprint(p + 1);
		strprint("'\n");
		return (0);
	}
	return (1);
}

/**
 * func_alias - mimics the alias builtin e.g (man alias)
 * @list: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int func_alias(inf_table *list)
{
	int i = 0;
	char *p = NULL;
	sll_table *node = NULL;

	if (list->agc == 1)
	{
		node = list->alias;
		while (node)
		{
			alias_printf(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; list->agv[i]; i++)
	{
		p = strchkr(list->agv[i], '=');
		if (p)
			func_make_alias(list, list->agv[i]);
		else
			alias_printf(node_starts_with(list->alias, list->agv[i], '='));
	}

	return (0);
}
