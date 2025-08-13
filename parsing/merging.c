#include "../minishell.h"

int	ft_count_arg(t_token *head)
{
	int	counter;

	counter = 0;
	while (head)
	{
		if (!is_redirection(head->type) && head->type != en_pip)
			counter++;
		if (head->type == en_pip)
			return (counter);
		if (is_redirection(head->type))
			head = head->next;
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
	cmd->exit_status = 0;
	cmd->len = 0;
	return (cmd);
}


void	fill_cmd_args(t_cmd **cmd, t_token *head)
{
	char	**av;
	int		i;
	
	i = 0;
	(*cmd)->len = ft_count_arg(head);
	av = malloc(sizeof(char *) * ((*cmd)->len + 1));
	// add the following check
	if ((*cmd)->len == 0)
		av = NULL;
	while (head && head->type != en_pip)
	{
		if (!is_redirection(head->type))
		{
			if (head->type == en_word && !head->value[0])
				av[i++] = NULL;
			else
				av[i++] = head->value;
			av[i] = NULL;
			head->readed = true;
		}
		else
			head = head->next;
		head = head->next;
	}
	(*cmd)->av = av;
}

t_redirection	*last_redirection(t_redirection *redirection)
{
	while (redirection->next)
		redirection = redirection->next;
	return (redirection);
}

void	fill_redirection_struct(t_token *head_token, t_cmd **cmd)
{
	t_cmd			*current_cmd;
	t_redirection	*new;

	current_cmd = *cmd;
	while (head_token && head_token->type != en_pip)
	{
		if (!head_token->readed)
		{
			new = new_node_redirection(head_token);
			if (!current_cmd->redirection)
				current_cmd->redirection = new;
			else
				last_redirection(current_cmd->redirection)->next = new;
			head_token = head_token->next;
		}
		head_token = head_token->next;
	}
}

void	merging(t_token *head, t_cmd **cmd)
{
	t_cmd	*current;
	
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
		fill_cmd_args(&current, head);
		fill_redirection_struct(head, &current);
		while (head && head->type != en_pip)
			head = head->next;
	}
}
