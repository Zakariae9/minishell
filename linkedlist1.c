#include "minishell.h"

t_token	*new_node(char *str, t_type type)
{
	t_token	*node = malloc(sizeof(t_token));
	
	node->value = str;
	node->type = type;
	node->join = false;
	node->expanding = en_dont_expand;
	node->next = NULL;
	return (node);
}

t_token	*last_node(t_token *head)
{
    if (head == NULL)
        return (head);
    while (head->next != NULL)
		head = head->next;
    return (head);
}

void	add_back(t_token **head, t_token *new)
{
	if (*head == NULL)
    {
        (*head) = new;
        return ;
    }
    last_node(*head)->next = new;
}

t_addresses	*node(void *value)
{
	t_addresses	*new;

	new = malloc(sizeof(t_addresses));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	push_back(t_addresses **head, t_addresses *new)
{
	t_addresses	*helper;

	helper = *head;
	if (helper == NULL)
	{
		*head = new;
		return ;
	}
	while (helper->next != NULL)
		helper = helper->next;
	helper->next = new;
}