#include "shell.h"

/**
 * **word_tok - spliting strings into words.
 * @st: the input string
 * @dl: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **word_tok(char *st, char *dl)
{
	int indx, x, f, mi, nw = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!dl)
		dl = " ";
	for (indx = 0; st[indx] != '\0'; indx++)
		if (!strdelim_checker(st[indx], dl) && (strdelim_checker(st[indx + 1], dl) || !st[indx + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (indx = 0, x = 0; x < nw; x++)
	{
		while (strdelim_checker(st[indx], dl))
			indx++;
		f = 0;
		while (!strdelim_checker(st[indx + f], dl) && st[indx + f])
			f++;
		s[x] = malloc((f + 1) * sizeof(char));
		if (!s[x])
		{
			for (f = 0; f < x; f++)
				free(s[f]);
			free(s);
			return (NULL);
		}
		for (mi = 0; mi < f; mi++)
			s[x][mi] = st[indx++];
		s[x][mi] = 0;
	}
	s[x] = NULL;
	return (s);
}
