#include "minishell.h"

t_env	*new_node_export(char *str)
{
	t_env	*node;
	char	*helper;

	node = malloc(sizeof(t_env));
	helper = ft_strchr(str, '=');
	node->value = ft_substr(helper + 1, 0, ft_strlen(helper));
	helper[0] = 0;
	node->var = ft_substr(str, 0, ft_strlen(str));
	node->next = NULL;
	return (node);
}

void	add_back_export(t_env **head, t_env *new)
{
	t_env	*current;

	current = *head;
	if (current == NULL)
	{
		*head = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

void	make_env_list(char **env, t_env	**head)
{
	int	i;

	i = -1;
	*head = NULL;
	while (env[++i])
		add_back_export(head, new_node_export(env[i]));
}

void	keep_only_space(t_token *head)
{
	while(head)
	{
		if (head->expanding == en_expand && head->type == en_word)
			head->value = delete_spaces(head->value);
		head = head->next;
	}
}

void	fixing_tokens(t_token *head)
{
	keep_only_space(head);
	join_tokens(head);
}
