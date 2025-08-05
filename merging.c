#include "minishell.h"
int	count_arg(t_token *head)
{
	int	counter;

	counter = 0;
	while (head)
	{
		if (head->type == en_word ||
			head->type == en_double_qoute ||
			head->type == en_single_qoute)
			counter++;
		else
			return (counter);
		head = head->next;
	}
	return (counter);
}

t_redir_type	redir_type(t_type type)
{
	if (type == en_output)
		return (REDIR_OUT);
	else if (type == en_input)
		return (REDIR_IN);
	else if (type == en_append)
		return (REDIR_APPEND);
	else
		return (REDIR_HEREDOC);
}

t_redirection	*new_node_redirection(t_token *head_token)
{
	t_redirection	*new_redir;

	new_redir = malloc(sizeof(t_redirection));
	new_redir->file_name = head_token->next->value;
	new_redir->type = redir_type(head_token->type);
	new_redir->next = NULL;
	return (new_redir);
}

t_cmd	*new_node_cmd()
{
	t_cmd	*cmd;

	cmd	= malloc(sizeof(t_cmd));
	cmd->av = NULL;
	cmd->next = NULL;
	cmd->redirection = NULL;
	return (cmd);
}

void	fill_av(int arg_num, char **av, t_token **head)
{
	int		i;

	i = 0;
	while (i < arg_num)
	{
		av[arg_num] = NULL;
		av[i] = (*head)->value;
		*head = (*head)->next;
		i++;
	}
}

void	fill_redirection_struct(t_token **head_token, t_cmd **cmd)
{
	t_cmd			*currernt_cmd;
	t_redirection	*new;
	t_token			*current_token;

	current_token = *head_token;
	currernt_cmd = *cmd;
	new = new_node_redirection(current_token);
	if (!currernt_cmd->redirection)
		currernt_cmd->redirection = new;
	else
		currernt_cmd->redirection->next = new;
	(*head_token) = (*head_token)->next->next;
}

void	merging(t_token *head, t_cmd **cmd)
{
	//int		i;
	int		arg_num;
	t_cmd	*current;
	char	**av;
	
	//i = 0;
	*cmd = new_node_cmd();
	current = *cmd;
	while (head)
	{
		if (head->type == en_pip)
		{
			current->next = new_node_cmd();
			current = current->next;
			head = head->next;
		}
		arg_num = count_arg(head);
		if (!current->av) // If i already fill av but i want to fill redirection again
			av = malloc(sizeof(char *) * (arg_num + 1));
		fill_av(arg_num, av, &head);
		if (head && is_redirection(head->type))
			fill_redirection_struct(&head, &current);
		current->av = av;
	}
}