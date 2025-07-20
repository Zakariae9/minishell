#include "minishell.h"

char	*get_address_of_closed_quote(char *command, char original_quote)
{
	command = ft_strchr(command, original_quote);
    return (ft_strchr(command + 1, original_quote));
}

int	convert_from_add_to_pos(char *str, char c)
{
	char	*address;

	address = ft_strchr(str, c);
	if (address == NULL)
		return (-1);
	return (address - str);
}

int	pos_of_end_of_variable(char *command, int start)
{
	int	i;
	int	pos;

	pos = 0;
	i = start + 1;
	if (command[i] == '?')
		return (1);
	while (ft_isalnum(command[i]) || command[i] == '_')
	{
		i++;
		pos++;
	}
	return (pos);
}

char	*get_address_of_separator(char *command)
{
	int	i;

	i = 0;
	while (command[i] != ' ' && command[i] != '<' && command[i] != '>' && command[i] != '|' && command[i] != '\0')
		i++;
	return (command + i);
}

void	join_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		while (current->join && current->next != NULL)
		{
			current->value = ft_strjoin(current->value, current->next->value);
			current->join = current->next->join;
			delete_tokens(&head, current->next->value);
		}
		current = current->next;
	}
}