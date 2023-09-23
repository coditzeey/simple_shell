#include "shell.h"

/**
 * num_conv - function to convert
 * @num: number
 * @b: base
 * @fgs: argument flags
 *
 * Return: string
 */
char *num_conv(long int num, int b, int fgs)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(fgs & CONV_INT_UNS) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = fgs & CONV_LC ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * stderrprint - writes a character to std err
 * @ch: character to print to stderr
 *
 * Return: On success 1.
 * On error, -1 is returned.
 */
int stderrprint(char ch)
{
	static int indx;
	static char buf[WRITE_BUFFER_SIZE];

	if (ch == FREE_BUFF || indx >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, indx);
		indx = 0;
	}
	if (ch != FREE_BUFF)
		buf[indx++] = ch;
	return (1);
}

/**
 * filedesc_print - writes character c to own file descriptor
 * @ch: character to print
 * @filedesc: The file descriptor to write.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int filedesc_print(char ch, int filedesc)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (ch == FREE_BUFF || i >= WRITE_BUFFER_SIZE)
	{
		write(filedesc, buf, i);
		i = 0;
	}
	if (ch != FREE_BUFF)
		buf[i++] = ch;
	return (1);
}

/**
 * rev_ascii_std - converts a string to an integer (just reverse ascii_std)
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int rev_ascii_std(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
