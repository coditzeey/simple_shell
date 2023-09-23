#include "shell.h"

/**
 **strcpi - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *strcpi(char *dest, char *src, int n)
{
	int indx, j;
	char *s = dest;

	indx = 0;
	while (src[indx] != '\0' && indx < n - 1)
	{
		dest[indx] = src[indx];
		indx++;
	}
	if (indx < n)
	{
		j = indx;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strcocate - this fuctio concatenates two idividual strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *strcocate(char *dest, char *src, int n)
{
	int indx, j;
	char *s = dest;

	indx = 0;
	j = 0;
	while (dest[indx] != '\0')
		indx++;
	while (src[j] != '\0' && j < n)
	{
		dest[indx] = src[j];
		indx++;
		j++;
	}
	if (j < n)
		dest[indx] = '\0';
	return (s);
}

/**
 **strchkr -  checks for character in a string
 *@s: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *strchkr(char *s, char ch)
{
	do {
		if (*s == ch)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
