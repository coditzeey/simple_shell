#include "shell.h"

/**
 * _strcmp - performs comparison of two strangs.
 * @st1: the first strang
 * @st2: the second strang
 *
 * Return: -1 if s1 < s2, 1 if s1 > s2, 0 if s1 == s2
 */
int _strcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 *
 * Return: the length of string.
 */
int _strlen(char *s)
{
	int c = 0;

	if (!s)
		return (0);

	for (c = 0; s[c] != 0; c++)
	;

	return (c);
}

/**
 * to_comp - check if @pointer is in string
 * @overflow: string to search
 * @pointer: the substring to look for
 *
 * Return: address of next char of overflow or NULL
 */
char *to_comp(const char *overflow, const char *pointer)
{
	while (*pointer)
		if (*pointer++ != *overflow++)
			return (NULL);
	return ((char *)overflow);
}

/**
 * _strconcat - concatenates or joins two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_strconcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
