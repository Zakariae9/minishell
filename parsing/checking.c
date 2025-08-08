#include "../minishell.h"

bool	check_redirection(t_token *head)
{
	while (head)
	{
		if (is_redirection(head->type) && is_redirection(head->next->type))
			return (true);
		head = head->next;
	}
	return (false);
}

bool	is_there_only$(char *command, t_type type)
{
	command = ft_strchr(command, '$');
	if (type == en_word)
		return (command[1] == '\0');
	return ((!command[1] || command[1] == ' ') && type == en_double_qoute);
}
