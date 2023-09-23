#include "shell.h"

/**
 * mem_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int mem_free(void **ptrr)
{
	if (ptrr && *ptrr)
	{
		free(*ptrr);
		*ptrr = NULL;
		return (1);
	}
	return (0);
}
