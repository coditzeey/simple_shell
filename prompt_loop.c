#include "shell.h"

/**
 * prompt_loop - main shell prompt loop
 * @list: the parameter & return list struct
 * @av: the argument vector from main function
 *
 * Return: 0 on success and 1 on error, or error code
 */
int prompt_loop(inf_table *list, char **av)
{
	int rec_inbuilt = 0;
	ssize_t x = 0;

	do {
		struct_init_(list);
		if (interactive_ses(list))
			strprint("$ ");
		stderrprint(FREE_BUFF);
		x = get_input(list);
		if (x != -1)
		{
			struct_init_md(list, av);
			rec_inbuilt = find_builtin(list);
			if (rec_inbuilt == -1)
				find_cmd(list);
		}
		else if (interactive_ses(list))
			charprint('\n');
		free_inf_table(list, 0);
	} while (x != -1 && rec_inbuilt != -2);

	write_history(list);
	free_inf_table(list, 1);
	if (!interactive_ses(list) && list->status)
		exit(list->status);
	if (rec_inbuilt == -2)
	{
		if (list->err_num == -1)
			exit(list->status);
		exit(list->err_num);
	}
	return (rec_inbuilt);
}

/**
 * find_builtin - finds a builtin command
 * @list: the parameter & return list struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(inf_table *list)
{
	int i, built_in_ret = -1;
	table_builtin builtintbl[] = {
		{"exit", func_exit},
		{"env", print_curr_env},
		{"help", help_func},
		{"history", func_history},
		{"setenv", make_env},
		{"unsetenv", rem_made_env},
		{"cd", cd_func},
		{"alias", func_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(list->agv[0], builtintbl[i].type) == 0)
		{
			list->lnc_var++;
			built_in_ret = builtintbl[i].func(list);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @list: the parameter & return list struct
 *
 * Return: void
 */
void find_cmd(inf_table *list)
{
	char *path = NULL;
	int i, k;

	list->path = list->agv[0];
	if (list->lnc_fvar == 1)
	{
		list->lnc_var++;
		list->lnc_fvar = 0;
	}
	for (i = 0, k = 0; list->arg[i]; i++)
		if (!strdelim_checker(list->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(list, get_envalue(list, "PATH="), list->agv[0]);
	if (path)
	{
		list->path = path;
		fork_cmd(list);
	}
	else
	{
		if ((interactive_ses(list) || get_envalue(list, "PATH=")
			|| list->agv[0][0] == '/') && is_cmd(list, list->agv[0]))
			fork_cmd(list);
		else if (*(list->arg) != '\n')
		{
			list->status = 127;
			err_printfunc(list, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @list: the parameter & return list struct
 *
 * Return: void
 */
void fork_cmd(inf_table *list)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(list->path, list->agv, getenv_info(list)) == -1)
		{
			free_inf_table(list, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(list->status));
		if (WIFEXITED(list->status))
		{
			list->status = WEXITSTATUS(list->status);
			if (list->status == 126)
				err_printfunc(list, "Permission denied\n");
		}
	}
}
