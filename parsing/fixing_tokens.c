/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixing_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboumei <zaboumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:41:30 by zaboumei          #+#    #+#             */
/*   Updated: 2025/08/17 17:28:42 by zaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	keep_only_space(t_token *head)
{
	while(head)
	{
		if (head->expanding == en_expand && head->type == en_word)
			head->value = delete_spaces(head->value);
		head = head->next;
	}
}

void	spliting_token_to_tokens(t_token *head, char c)
{
	t_token	*new;
	char	*temp;
	char	*add;

	while (head)
	{
		if (head->expanding == en_expand && head->type == en_word)
		{
			add = ft_strchr(head->value, c);
			if (!add)
				break;
			new = new_node(add + 1, en_word); // don't forget get were it should stop
			new->value = ft_strdup(new->value);
			temp = head->value;
			head->value = delete_part(head->value, add);
			//free(temp);
			new->next = head->next;
			head->next = new;
		}
		head = head->next;
	}
}

void	delete_tokens_NULL(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (!current->value[0] && current->expanding == en_expand
			&& current->type == en_word)
			delete_token(head, current);
		current = current->next;
	}
}

bool	is_emtystr_followed_redi(t_token *head)
{
	while (head)
	{
		if (head->next && is_redirection(head->type) && !head->next->value[0])
			return (1);
		head = head->next;
	}
	return (false);
}

void	fixing_tokens(t_token **head)
{
	keep_only_space(*head);
	join_tokens(*head);
	spliting_token_to_tokens(*head, ' ');
	if (!is_emtystr_followed_redi(*head))
		delete_tokens_NULL(head);
}
void	delete_token(t_token **head, t_token *address)
{
	t_token	*current;
	t_token	*previous;

	current = *head;
	previous = current;
	if (current == address)
	{
		(*head) = current->next;
		free_token(&current);
		return ;
	}
	while (current != address)
	{
		previous = current;
		current = current->next;
	}
	previous->next = current->next;
	free_token(&current);
}
