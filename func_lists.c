#include "shell.h"

/**
 * create_node - creates a node in the start of the list
 * @head: head node
 * @str: string field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
sll_table *create_node(sll_table **head, const char *str, int num)
{
	sll_table *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(sll_table));
	if (!new_head)
		return (NULL);
	memfill((void *)new_head, 0, sizeof(sll_table));
	new_head->num = num;
	if (str)
	{
		new_head->st = duplstr(str);
		if (!new_head->st)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * create_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
sll_table *create_node_end(sll_table **head, const char *str, int num)
{
	sll_table *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(sll_table));
	if (!new_node)
		return (NULL);
	memfill((void *)new_node, 0, sizeof(sll_table));
	new_node->num = num;
	if (str)
	{
		new_node->st = duplstr(str);
		if (!new_node->st)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a sll_table linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const sll_table *h)
{
	size_t i = 0;

	while (h)
	{
		strprint(h->st ? h->st : "(nil)");
		strprint("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_speci_index - deletes node at any index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_speci_index(sll_table **head, unsigned int index)
{
	sll_table *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->st);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->st);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_nds_list - frees all nodes
 * @head_ptrr: address of pointer to head node
 *
 * Return: void
 */
void free_nds_list(sll_table **head_ptrr)
{
	sll_table *node, *next_node, *head;

	if (!head_ptrr || !*head_ptrr)
		return;
	head = *head_ptrr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->st);
		free(node);
		node = next_node;
	}
	*head_ptrr = NULL;
}
