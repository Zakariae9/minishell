#include "minishell.h"

void clean_and_exit(int exit_code)
{
	gc_malloc(en_free, 0);
	exit(exit_code);
}

void cleanup(void)
{
	clear_history();
	gc_malloc(en_free, 0);
}


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
			free(temp->content);
			free(temp);
			temp = next;
		}
		*lst = NULL;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_helper;

	if (lst == NULL)
		return (lst);
	lst_helper = lst;
	while (lst_helper->next != NULL)
	{
		lst_helper = lst_helper->next;
	}
	return (lst_helper);
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

void	*gc_malloc(t_gc gc, size_t size)
{
	static	t_list	*head = NULL;
	void			*lst;

	if (gc == en_malloc)
	{
		lst = malloc(size);
		if (!lst)
		{
			perror("malloc");
			cleanup();
		}
		ft_lstadd_back(&head, ft_lstnew(lst));
	}
	if (gc == en_free)
	{
		ft_lstclear(&head);
		head = NULL;
		return (NULL);
	}
	if (gc == en_get_head)
		return (head);
	return (lst);
}
void gc_register(void *ptr)
{
	t_list	*head;

	head = gc_malloc(en_get_head, 0);
	ft_lstadd_back(&head, ft_lstnew(ptr));
}
