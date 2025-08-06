/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 05:41:47 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/06 05:47:52 by mel-hafi         ###   ########.fr       */
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

int	handle_redirections(t_redirection *redir_list)
{
	t_redirection	*curr;
	int				last_heredoc_fd;

	curr = redir_list;
	last_heredoc_fd = -1;
	while (curr)
	{
		if (curr->type == REDIR_IN && handle_redir_in(curr->file_name))
			return (1);
		else if (curr->type == REDIR_OUT && handle_redir_out(curr->file_name))
			return (1);
		else if (curr->type == REDIR_APPEND
			&& handle_redir_append(curr->file_name))
			return (1);
		else if (curr->type == REDIR_HEREDOC)
			last_heredoc_fd = curr->heredoc_fd;
		curr = curr->next;
	}
	if (last_heredoc_fd != -1)
	{
		if (dup2(last_heredoc_fd, STDIN_FILENO) == -1)
			return (perror("dup2 heredoc"), close(last_heredoc_fd), 1);
		close(last_heredoc_fd);
	}
	return (0);
}
