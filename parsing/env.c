/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:36:12 by zaboumei          #+#    #+#             */
/*   Updated: 2025/08/17 09:30:04 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_node_export(char *str)
{
	t_env	*node;
	char	*helper;

	node = gc_malloc(en_malloc, sizeof(t_env));
	helper = ft_strchr(str, '=');
	node->value = ft_substr(helper + 1, 0, ft_strlen(helper) - 1); //invalid read without -1 i think 
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
