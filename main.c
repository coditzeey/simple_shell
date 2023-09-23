#include "shell.h"

/**
 * main - i guess we all know what it does (:
 * @agc: argument counter retursn integer
 * @agv: argument vector returns integer
 *
 * Return: 0 on success and 1 if error
 */

int main(int agc, char **agv)
{
	inf_table list[] = { INFO_INITIALIZE };
	long int nkowa = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=re" (nkowa)
		: "re" (nkowa));

	if (agc == 2)
	{
		nkowa = open(agv[1], O_RDONLY);
		if (nkowa == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				input_printff(agv[0]);
				input_printff(": 0: file reading failed ");
				input_printff(agv[1]);
				stderrprint('\n');
				stderrprint(FREE_BUFF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		list->rdfldesc = nkowa;
	}
	add_to_envlist(list);
	get_history_func(list);
	prompt_loop(list, agv);
	return (EXIT_SUCCESS);
}
