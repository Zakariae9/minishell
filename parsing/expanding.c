#include "../minishell.h"

void	expanding_all_tokens(t_token *head, t_env *head_env, int *exit_status)
{
	t_token	*helper;

	helper = head;
	deside_expanding(helper);
	while (helper)
	{
		if (helper->expanding == en_expand)
			helper->value = expanding(helper->value, head_env, exit_status);
		helper = helper->next;
	}
}

char	*expand_exit_status(char *command, t_expand_var *expand, t_addresses **head, int *exit_status)
{
	push_back(head, node(command));
	command = add_str(command, ft_itoa(*exit_status), expand->start);
	push_back(head, node(command));
	command = delete_part(command, expand->helper);
	push_back(head, node(expand->helper));
	return (command);
}

char	*expanding(char *command, t_env *head_env, int *exit_status)
{
	t_expand_var	expand;
	t_addresses	*head;

	head = NULL;
	expand.num = num_of_char(command, '$');
	while (expand.num--)
	{
		expand.helper = get_variable_for_expanding(command, &expand.start, &expand.end_pos);
		if (!ft_strcmp(expand.helper, "$?"))
		{
			command = expand_exit_status(command, &expand, &head, exit_status);
			continue ;
		}
		expand.env = ft_getenv(expand.helper + 1, head_env);
		if (expand.env != NULL)
		{
			push_back(&head, node(command));
			command = add_str(command, expand.env, expand.start);
		}
		push_back(&head, node(command));
		command = delete_part(command, expand.helper);
		push_back(&head, node(expand.helper));
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
		if (head->type == en_heredoc)
			head->next->expanding = en_should_not;
		if ((head->type == en_word || head->type == en_double_qoute)
			&& head->expanding != en_should_not)
		{
			if (num_of_char(head->value, '$') > 0 && !is_there_only$(head->value, head->type))
				head->expanding = en_expand;
		}
		head = head->next;
	}
}
