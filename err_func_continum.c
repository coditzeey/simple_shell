#include "shell.h"

/**
 * output_fd - prints an input string
 * @str:  string to be printed
 * @filedesc: the file descriptor to write
 *
 * Return: the number of chars put
 */
int output_fd(char *str, int filedesc)
{
	int indx = 0;

	if (!str)
		return (0);
	while (*str)
	{
		indx += filedesc_print(*str++, filedesc);
	}
	return (indx);
}


/**
 * err_printfunc - outputs error message
 * @list: the parameter & return list struct
 * @errstr: string containing specific error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void err_printfunc(inf_table *list, char *errstr)
{
	input_printff(list->fname);
	input_printff(": ");
	dec_print(list->lnc_var, STDERR_FILENO);
	input_printff(": ");
	input_printff(list->agv[0]);
	input_printff(": ");
	input_printff(errstr);
}

/**
 * dec_print - print a decimal (integer) number
 * @input: the input
 * @filedesc: file descriptor to write
 *
 * Return: number of characters printed
 */
int dec_print(int input, int filedesc)
{
	int (*__putchar)(char) = charprint;
	int indx, count = 0;
	unsigned int _abs_, current;

	if (filedesc == STDERR_FILENO)
		__putchar = stderrprint;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (indx = 1000000000; indx > 1; indx /= 10)
	{
		if (_abs_ / indx)
		{
			__putchar('0' + current / indx);
			count++;
		}
		current %= indx;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 *input_printff - prints an input string
 * @st: the string to be printed
 *
 * Return: Nothing
 */
void input_printff(char *st)
{
	int indx = 0;

	if (!st)
		return;
	while (st[indx] != '\0')
	{
		stderrprint(st[indx]);
		indx++;
	}
}

/**
 * coms_rem - replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void coms_rem(char *buffer)
{
	int indx;

	for (indx = 0; buffer[indx] != '\0'; indx++)
		if (buffer[indx] == '#' && (!indx || buffer[indx - 1] == ' '))
		{
			buffer[indx] = '\0';
			break;
		}
}
