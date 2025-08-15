#include "minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*next;

	if (lst)
	{
		temp = *lst;
		while (temp != NULL)
		{
			next = temp->next;
			free(temp);
			temp = next;
		}
		*lst = NULL;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

void	*gc_malloc(void *lst, t_gc gc, size_t size)
{
	static	void	*head = NULL;

	if (gc == en_malloc)
		return (malloc(size));
	if (gc == en_free)
	{
		ft_lstclear(&lst);
		return ;
	}
	ft_lstadd_back(&head, ft_lstnew(lst));
	return (NULL);
}
