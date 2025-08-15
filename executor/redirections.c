/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 05:41:47 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/09 04:10:26 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redir_in(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open infile"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2 infile"), close(fd), 1);
	close(fd);
	return (0);
}

int	handle_redir_out(const char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open outfile"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2 outfile"), close(fd), 1);
	close(fd);
	return (0);
}

int	handle_redir_append(const char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror("open append"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2 append"), close(fd), 1);
	close(fd);
	return (0);
}

int	handle_one_redirection(t_redirection *redir)
{
	if (redir->type == REDIR_IN)
		return (handle_redir_in(redir->file_name));
	if (redir->type == REDIR_OUT)
		return (handle_redir_out(redir->file_name));
	if (redir->type == REDIR_APPEND)
		return (handle_redir_append(redir->file_name));
	if (redir->type == REDIR_HEREDOC)
	{
		if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			close(redir->heredoc_fd);
			return (1);
		}
		close(redir->heredoc_fd);
		return (0);
	}
	return (0);
}

int	handle_redirections(t_redirection *redir_list)
{
	t_redirection	*curr;

	curr = redir_list;
	while (curr)
	{
		if (handle_one_redirection(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}
