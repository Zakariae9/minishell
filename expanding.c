#include "minishell.h"

void	expanding_all_tokens(t_token *head, t_env *head_env)
{
	t_token	*helper;
	helper = head;
	deside_expanding(helper);
	while (helper)
	{
		if (helper->expanding == en_expand)
			helper->value = expanding(helper->value, head_env);
		helper = helper->next;
	}
	if (len_list(head) > 1)
		delete_tokens(&head, "");
}

char	*expanding(char *command, t_env *head_env)
{
	int			end_pos;
	int			start;
	int			num;
	char		*env;
	char		*helper;
	t_addresses	*head;

	head = NULL;
	num = num_of_char(command, '$');
	while (num--)
	{
		helper = get_variable_for_expanding(command, &start, &end_pos);
		env = ft_getenv(helper + 1, head_env);
		if (env != NULL)
		{
			push_back(&head, node(command));
			command = add_str(command, env, start);
		}
		push_back(&head, node(command));
		command = delete_part(command, helper);
		push_back(&head, node(helper));
	}
	return (free_address(head), command);
}

char	*get_variable_for_expanding(char *command, int *start, int *end_pos)
{
	char	*var_with_$;

	*start = convert_from_add_to_pos(command, '$');
	*end_pos = pos_of_end_of_variable(command, *start);
	var_with_$ = ft_substr(command, *start, (*end_pos) + 1);
	return (var_with_$);
}

void	deside_expanding(t_token *head)
{
	while (head)
	{
		if (head->type == en_word || head->type == en_double_qoute)
		{
			if (num_of_char(head->value, '$') > 0 && !is_there_only$_as_double_q(head->value, head->type))
				head->expanding = en_expand;
		}
		head = head->next;
	}
}

void	delete_tokens(t_token	**head, char *data)
{
	t_token	*current;
	t_token	*previous;

	current = *head;
	previous = current;
	while (current)
	{
		if (ft_strcmp(data, current->value) == 0)
		{
			previous->next = current->next;
			free_token(&current);
			current = previous;
		}
		previous = current;
		current = current->next;
	}
}
