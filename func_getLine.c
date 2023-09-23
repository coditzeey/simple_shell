#include "shell.h"

/**
 * chain_buffers - buffers chained commands
 * @list: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t chain_buffers(inf_table *list, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*mem_free((void **)list->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if GETLINE_MAC
		r = getline(buf, &len_p, stdin);
#else
		r = nline_input(list, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			list->lnc_fvar = 1;
			coms_rem(*buf);
			build_history_list(list, *buf, list->hist_ln_count++);
			{
				*len = r;
				list->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * inputcmd_chain - gets a line minus the newline
 * @list: parameter struct
 *
 * Return: bytes read
 */
ssize_t inputcmd_chain(inf_table *list)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(list->arg), *p;

	charprint(FREE_BUFF);
	r = chain_buffers(list, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		verify_seq(list, buf, &j, i, len);
		while (j < len)
		{
			if (is_seq(list, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			list->cmd_buf_type = CLI_NORMAL;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @list: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(inf_table *list, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(list->rdfldesc, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * nline_input - receives next line of input from STDIN
 * @list: parameter
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int nline_input(inf_table *list, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(list, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchkr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = mem_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strcocate(new_p, buf + i, k - i);
	else
		strcpi(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - key ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	strprint("\n");
	strprint("$ ");
	charprint(FREE_BUFF);
}
