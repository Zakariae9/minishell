#include "../minishell.h"

bool	check_are_qoutes_open(char *command)
{
	char	qoute;
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			qoute = command[i];
			i++;
			while (command[i] != qoute && command[i])
				i++;
			if (!command[i])
				return (true);
		}
		i++;
	}
	return (false);
}

bool	is_firs_and_last_token_valid(t_token *head)
{
	if ((head->type != en_word && head->type != en_double_qoute && en_single_qoute != head->type
		&& head->type != en_heredoc))
		return (false);
	while (head->next)
		head = head->next;
	if (head->type != en_word && head->type != en_double_qoute && head->type != en_single_qoute)
		return (false);
	return (true);
}

bool	are_bash_rules_correct(t_token *head)
{
	if (is_firs_and_last_token_valid(head) && !is_there_anything_else(head) && !check_redirection(head))
		return (1);
	return (0);
}

int	is_there_anything_else(t_token *head)
{
	while (head != NULL)
	{
		if (head->type == en_anything_else )
			return (1);
		head = head->next;
	}
	return (0);
}
