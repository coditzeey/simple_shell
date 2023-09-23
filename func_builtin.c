#include "shell.h"

/**
 * func_exit - exit the shell
 * @list: Used to maintain constant function prototype.
 *
 *  Return: exits with a given exit status
 *         (0) if list.argv[0] != "exit"
 */
int func_exit(inf_table *list)
{
	int exit_func;

	if (list->agv[1])  /* If there is an exit command */
	{
		exit_func = rev_ascii_std(list->agv[1]);
		if (exit_func == -1)
		{
			list->status = 2;
			err_printfunc(list, "Number Unknown: ");
			input_printff(list->agv[1]);
			stderrprint('\n');
			return (1);
		}
		list->err_num = rev_ascii_std(list->agv[1]);
		return (-2);
	}
	list->err_num = -1;
	return (-2);
}

/**
 * cd_func - changes the current path/directory of process
 * @list: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int cd_func(inf_table *list)
{
	char *s, *dir, buffer[1024];
	int cwd_rec;

	s = getcwd(buffer, 1024);
	if (!s)
		strprint("TODO: >>getcwd emsg coming soon<<\n");
	if (!list->agv[1])
	{
		dir = get_envalue(list, "HOME=");
		if (!dir)
			cwd_rec =
			chdir((dir = get_envalue(list, "PWD=")) ? dir : "/");
		else
			cwd_rec = chdir(dir);
	}
	else if (_strcmp(list->agv[1], "-") == 0)
	{
		if (!get_envalue(list, "OLDPWD="))
		{
			strprint(s);
			charprint('\n');
			return (1);
		}
		strprint(get_envalue(list, "OLDPWD=")), charprint('\n');
		cwd_rec =
			chdir((dir = get_envalue(list, "OLDPWD=")) ? dir : "/");
	}
	else
		cwd_rec = chdir(list->agv[1]);
	if (cwd_rec == -1)
	{
		err_printfunc(list, "failed  to cd ");
		input_printff(list->agv[1]), stderrprint('\n');
	}
	else
	{
		set_new_env(list, "OLDPWD", get_envalue(list, "PWD="));
		set_new_env(list, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_func - help function
 * @list: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int help_func(inf_table *list)
{
	char **ag_array;

	ag_array = list->agv;
	strprint("my TODOS : Function not yet implemented \n");
	if (0)
		strprint(*ag_array);
	return (0);
}
