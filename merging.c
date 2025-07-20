#include "minishell.h"


// Helper: Count arguments for a command (until pipe or end)
/*int count_args(t_token *token)
{
    int count = 0;
    while (token && token->type != en_pip)
    {
        if (token->type != en_output && token->type != en_input &&
            token->type != en_append && token->type != en_heredoc)
            count++; // Count tokens like en_word for av
        else
        {
            token = token->next; // Skip redirection file
            if (!token)
                break;
        }
        token = token->next;
    }
    return count;
}

// Helper: Add a redirection to t_cmd
int add_redirection(t_cmd *cmd, t_redir_type type, char *file_name)
{
    if (!file_name)
        return 0; // Error: missing file name
    t_redirection *new = malloc(sizeof(t_redirection));
    if (!new)
        return 0;
    new->type = type;
    new->file_name = ft_strdup(file_name);
    if (!new->file_name)
    {
        free(new);
        return 0;
    }
    new->next = NULL;

    if (!cmd->redirection)
        cmd->redirection = new;
    else
    {
        t_redirection *current = cmd->redirection;
        while (current->next)
            current = current->next;
        current->next = new;
    }
    return 1;
}

// Helper: Free t_cmd list
void free_cmd_list(t_cmd *cmd)
{
    while (cmd)
    {
        t_cmd *next = cmd->next;
        for (int i = 0; cmd->av && cmd->av[i]; i++)
            free(cmd->av[i]);
        free(cmd->av);
        t_redirection *redir = cmd->redirection;
        while (redir)
        {
            t_redirection *next_redir = redir->next;
            free(redir->file_name);
            free(redir);
            redir = next_redir;
        }
        free(cmd);
        cmd = next;
    }
}

// Main function: Convert t_token list to t_cmd list
t_cmd *tokens_to_commands(t_token *tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = NULL;
    t_token *current_token = tokens;
    char **av = NULL;
    int arg_count = 0;
    int arg_index = 0;

    while (current_token)
    {
        // Start a new command (for first command or after pipe)
        if (!current_cmd || current_token->type == en_pip)
        {
            if (current_token && current_token->type == en_pip) // tkon pipe
                current_token = current_token->next; // Skip pipe token
            t_cmd *new_cmd = malloc(sizeof(t_cmd));
            if (!new_cmd)
            {
                free_cmd_list(cmd_list);
                return NULL;
            }
            new_cmd->av = NULL;
            new_cmd->redirection = NULL;
            new_cmd->next = NULL;
            if (!cmd_list)
                cmd_list = new_cmd;
            else
                current_cmd->next = new_cmd;
            current_cmd = new_cmd;

            // Count arguments for this command (e.g., "ls", "-a")
            arg_count = count_args(current_token);
            av = malloc(sizeof(char *) * (arg_count + 1));
            if (!av)
            {
                free_cmd_list(cmd_list);
                return NULL;
            }


            av[0] = NULL; // Initialize av
            arg_index = 0;
        }

        // Process tokens for the current command
        if (current_token->type != en_pip &&
            current_token->type != en_output &&
            current_token->type != en_input &&
            current_token->type != en_append &&
            current_token->type != en_heredoc)
        {
            // Add to av (e.g., "ls", "-a")
            av[arg_index] = ft_strdup(current_token->value);
            if (!av[arg_index])
            {
                free_cmd_list(cmd_list);
                return NULL;
            }
            arg_index++;
        }
        else if (current_token->type == en_input)
        {
            current_token = current_token->next; // Move to file name
            if (!current_token || !add_redirection(current_cmd, REDIR_IN, current_token ? current_token->value : NULL))
            {
                free_cmd_list(cmd_list);
                return NULL;
            }
        }
        else if (current_token->type == en_output)
        {
            current_token = current_token->next; // Move to file name (e.g., "f1")
            if (!current_token || !add_redirection(current_cmd, REDIR_OUT, current_token ? current_token->value : NULL))
            {
                free_cmd_list(cmd_list);
                return NULL;
            }
        }
        else if (current_token->type == en_append)
        {
            current_token = current_token->next; // Move to file name
            if (!current_token || !add_redirection(current_cmd, REDIR_APPEND, current_token ? current_token->value : NULL))
            {
                free_cmd_list(cmd_list);
                return NULL;
            }
        }
        else if (current_token->type == en_heredoc)
        {
            current_token = current_token->next; // Move to delimiter
            if (!current_token || !add_redirection(current_cmd, REDIR_HEREDOC, current_token ? current_token->value : NULL))
            {
                free_cmd_list(cmd_list);
                return NULL;
            }
        }

        current_token = current_token->next;

        // Finalize command's av if no more tokens or at a pipe
        if (!current_token || current_token->type == en_pip)
        {
            av[arg_index] = NULL; // Null-terminate av
            current_cmd->av = av;
            av = NULL;
        }
    }

    return cmd_list;
}*/


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
	int		i;
	int		arg_num;
	t_cmd	*current;
	char	**av;
	
	i = 0;
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
