#include "shell.h"

/**
 * struct_init_ - initializes inf_table
 * @list: struct address
 */
void struct_init_(inf_table *list)
{
	list->arg = NULL;
	list->agv = NULL;
	list->path = NULL;
	list->agc = 0;
}

/**
 * struct_init_md - initializes inf_table struct
 * @list: struct address
 * @av: argument vector
 */
void struct_init_md(inf_table *list, char **av)
{
	int indx = 0;

	list->fname = av[0];
	if (list->arg)
	{
		list->agv = word_tok(list->arg, " \t");
		if (!list->agv)
		{

			list->agv = malloc(sizeof(char *) * 2);
			if (list->agv)
			{
				list->agv[0] = duplstr(list->arg);
				list->agv[1] = NULL;
			}
		}
		for (indx = 0; list->agv && list->agv[indx]; indx++)
			;
		list->agc = indx;

		manip_alias(list);
		vard_rep(list);
	}
}

/**
 * free_inf_table - frees inf_table struct fields
 * @list: struct address
 * @all: true if freeing all fields
 */
void free_inf_table(inf_table *list, int all)
{
	free_strs(list->agv);
	list->agv = NULL;
	list->path = NULL;
	if (all)
	{
		if (!list->cmd_buf)
			free(list->arg);
		if (list->env)
			free_nds_list(&(list->env));
		if (list->history)
			free_nds_list(&(list->history));
		if (list->alias)
			free_nds_list(&(list->alias));
		free_strs(list->environ);
			list->environ = NULL;
		mem_free((void **)list->cmd_buf);
		if (list->rdfldesc > 2)
			close(list->rdfldesc);
		charprint(FREE_BUFF);
	}
}
