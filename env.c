/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboumei <zaboumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:36:12 by zaboumei          #+#    #+#             */
/*   Updated: 2025/08/06 22:19:05 by zaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*void    split_single_space_token(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        // Condition: The node is marked for expansion and it contains a space.
        if (current->expanding == en_expand && ft_strchr(current->value, ' '))
        {
            // Find the exact location of the space.
            char *space_location = ft_strchr(current->value, ' ');

            // If a space was indeed found...
            if (space_location)
            {
                // --- STEP 1: Create a new node with the value "t" ---
                // We copy the string starting ONE character AFTER the space.
                char *new_value = ft_strdup(space_location + 1);
                t_token *new_t_node = new_node(new_value, current->type);

                // --- STEP 2: Insert the new node right after the current one ---
                new_t_node->next = current->next;
                current->next = new_t_node;

                // --- STEP 3: Modify the original node's value to "echo" ---
                // We "cut" the original string by placing a null terminator
                // where the space was.
                *space_location = '\0';
                
                // Now, current->value is just "echo"
                current->expanding = en_dont_expand; // Mark as done.

                // Advance current to the node we just inserted to continue the loop
                current = current->next;
            }
        }
        
        // Move to the next node in the list
        current = current->next;
    }
}*/

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
			free(temp);
			new->next = head->next;
			head->next = new;
		}
		head = head->next;
	}
}

void	fixing_tokens(t_token **head)
{
	t_token	*current = *head;
	keep_only_space(*head);
	join_tokens(*head);
	spliting_token_to_tokens(*head, ' ');
	while (current)
	{
		if (!current->value[0] && current->expanding == en_expand && current->type == en_word)
			delete_token(head, current);
		current = current->next;
	}
}
