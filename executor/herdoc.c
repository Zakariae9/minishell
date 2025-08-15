/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboumei <zaboumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 05:41:50 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/15 20:35:50 by zaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);
}

static void	heredoc_child(int write_fd, t_env *env, char *delimiter, bool qoute)
{
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("\nminishell: warning: here-document delimited by end-of-file\n");
			break;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (!qoute)
			line = expanding(line, env);
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
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
		heredoc_child(fds[1], env ,delimiter, qoute);
	}
	close(fds[1]);
	return (heredoc_parent(pid, fds[0]));
}


int prepare_all_heredocs(t_cmd *cmd_list, t_env *env)
{
    t_cmd *cmd = cmd_list;
    while (cmd)
    {
        t_redirection *redir = cmd->redirection;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                int fd = handle_heredoc(redir->file_name, env, redir->qoute);
                if (fd == -2)
                    return 130;
                if (fd < 0)
                    return (1);
                redir->heredoc_fd = fd;
            }
            redir = redir->next;
        }
        cmd = cmd->next;
    }
    return (0);
}
