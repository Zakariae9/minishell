#include "minishell.h"

char    *skip_spaces(char *command)
{
    int i = 0;
    
    while ((command[i] >= 9 && command[i] <= 13) || command[i] == ' ')
        i++;
    return command + i;
}

void	lexer(char *command, t_token **head)
{
	command = skip_spaces(command);
	while (command[0])
	{
		command = skip_spaces(command);
		if (!command[0])
			return ;
		else if (command[0] == '\'' || command[0] == '"')
			command = token_with_q(command, command[0], head);
		else if (command[0] == '|' || command[0] == '>' || command[0] == '<')
			command = token_delemeter(command, head);
		else
			command = token_without_q(command, head);
	}
}

char	*token_with_q(char *command, char q_type, t_token **head)
{
	char	*temp;
	t_token	*address;
	int		len;
	
	len = get_address_of_closed_quote(command, q_type) - command;
	temp = ft_substr(command, 1, len - 1);
	address = new_node(temp, witch_type(command[0], command[1]));
	if (command[len] != ' ' && command[len] != '|' && command[len] != '<' && command[len] != '>' && command[len])
		address->join = true;
	add_back(head, address);
	return (command + len + 1);
}

char	*token_delemeter(char *command, t_token **head)
{
	t_token	*address;
	char	*temp;
	short	i;

	i = 1;
	if (command[0] == command[1])
	{
		temp = ft_substr(command, 0, 2);
		i++;
	}
	else
		temp = ft_substr(command, 0, 1);
	address = new_node(temp, witch_type(command[0], command[1]));
	if (command[i] != ' ' && command[i] != '|' && command[i] != '<' && command[i] != '>' && command[i])
		address->join = true;
	add_back(head, address);
	return (command + i);
}

char	*token_without_q(char *command, t_token **head)
{
	char	*temp;
	int		i;
	t_token	*address;

	i = 0;
	while (command[i] != ' ' && command[i] != '|' && command[i] != '>' && command[i] != '<' && command[i] != '\0' && command[i] != '\'' && command[i] != '\"')
		i++;
	temp = ft_substr(command, 0, i);
	address = new_node(temp, en_word);
	if (command[i] != ' ' && command[i] != '|' && command[i] != '<' && command[i] != '>' && command[i])
		address->join = true;
	add_back(head, address);
	return (command + i);
}
