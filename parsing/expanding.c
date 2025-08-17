#include "../minishell.h"

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
}

char	*expand_exit_status(char *command, t_expand_var *expand)
{
	command = add_str(command, ft_itoa(get_exit_code(-1)), expand->start);
	command = delete_part(command, expand->helper);
	return (command);
}

char	*expanding(char *command, t_env *head_env)
{
	t_expand_var	expand;

	expand.num = num_of_char(command, '$');
	while (expand.num--)
	{
		expand.helper = get_variable_for_expanding(command, &expand.start, &expand.end_pos);
		if (!ft_strcmp(expand.helper, "$?"))
		{
			command = expand_exit_status(command, &expand);
			continue ;
		}
		expand.env = ft_getenv(expand.helper + 1, head_env);
		if (expand.env != NULL)
			command = add_str(command, expand.env, expand.start);
		command = delete_part(command, expand.helper);
	}
	return (command);
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
			if (num_of_char(head->value, '$') > 0 && !is_there_only_dolor(head->value, head->type))
				head->expanding = en_expand;
		}
		head = head->next;
	}
}
