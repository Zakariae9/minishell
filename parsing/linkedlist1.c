#include "../minishell.h"

t_token	*new_node(char *str, t_type type)
{
	t_token	*node = gc_malloc(en_malloc, sizeof(t_token));
	
	node->value = str;
	node->type = type;
	node->join = false;
	node->readed = false;
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

