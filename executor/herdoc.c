/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 05:41:50 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/19 09:21:53 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	get_fd(-1);
	clean_and_exit(130);
}

void	heredoc_child(int write_fd, t_env *env, char *delimiter, bool qoute)
{
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	get_fd(write_fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2,
				"\nminishell: warning: here-document delimited by end-of-file\n",
				61);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			break ;
		}
		if (!qoute)
			line = expanding(line, env);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
	}
	close(write_fd);
	clean_and_exit(0);
}

int	heredoc_parent(pid_t pid, int read_fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(read_fd);
		return (-2);
	}
	return (read_fd);
}

int	handle_heredoc(char *delimiter, t_env *env, bool qoute)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(fds[0]);
		heredoc_child(fds[1], env, delimiter, qoute);
	}
	close(fds[1]);
	return (heredoc_parent(pid, fds[0]));
}

int	prepare_all_heredocs(t_cmd *cmd_list, t_env *env)
{
	t_cmd			*cmd;
	t_redirection	*redir;
	int				fd;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirection;
		if (redir)
			redir->heredoc_fd = -1;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				fd = handle_heredoc(redir->file_name, env, redir->qoute);
				if (fd == -2)
					return (130);
				if (fd < 0)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
