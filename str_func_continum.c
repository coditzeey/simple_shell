#include "shell.h"

/**
 *strprint - prints an input string
 *@str: the string to be printed
 *
 * Return: No Value
 */
void strprint(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		charprint(str[i]);
		i++;
	}
}

/**
 * duplstr - duplicates a string
 * @st: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplstr(const char *st)
{
	int len = 0;
	char *get;

	if (st == NULL)
		return (NULL);
	while (*st++)
		len++;
	get = malloc(sizeof(char) * (len + 1));
	if (!get)
		return (NULL);
	for (len++; len--;)
		get[len] = *--st;
	return (get);
}

/**
 * cpystr - the function copy string
 * @start: the destination
 * @finish: the source
 *
 * Return: pointer to destination
 */
char *cpystr(char *start, char *finish)
{
	int i = 0;

	if (start == finish || finish == 0)
		return (start);
	while (finish[i])
	{
		start[i] = finish[i];
		i++;
	}
	start[i] = 0;
	return (start);
}

/**
 * charprint - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: 1 On success.
 * On error, -1 is returned, and errno is set appropriately.
 */
int charprint(char ch)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (ch == FREE_BUFF || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != FREE_BUFF)
		buf[i++] = ch;
	return (1);
}
