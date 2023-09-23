#include "shell.h"

/**
 * interactive_ses - returns true if shell is in interactive session mode
 * @list: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_ses(inf_table *list)
{
	return (isatty(STDIN_FILENO) && list->rdfldesc <= 2);
}

/**
 * strdelim_checker - checks if character is a delimeter
 * @ch: char variable to check
 * @dl: delimeter string
 * Return: 1 if true, 0 if false
 */
int strdelim_checker(char ch, char *dl)
{
	while (*dl)
		if (*dl++ == ch)
			return (1);
	return (0);
}

/**
 *is_alpha_check - checks for alphabet characters
 *@c: character input
 *Return: 1 if c is alphabetic and 0 otherwise
 */

int is_alpha_check(int c)
{
	if ((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *ascii_std - converts a string to an integer ascii standard
 *@st: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int ascii_std(char *st)
{
	int indx, sign = 1, sap = 0, output;
	unsigned int result = 0;

	for (indx = 0;  st[indx] != '\0' && sap != 2; indx++)
	{
		if (st[indx] == '-')
			sign *= -1;

		if (st[indx] >= '0' && st[indx] <= '9')
		{
			sap = 1;
			result *= 10;
			result += (st[indx] - '0');
		}
		else if (sap == 1)
			sap = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
