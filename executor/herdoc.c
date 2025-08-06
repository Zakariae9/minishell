/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 05:41:50 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/06 05:41:51 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);
}

int handle_heredoc(const char *delimiter)
{
    int fds[2];
    pid_t pid;
    int status;

    if (pipe(fds) == -1)
        return -1;

    pid = fork();
    if (pid == -1)
        return -1;

    if (pid == 0)
    {
        // Child process
        struct sigaction act;
        act.sa_handler = heredoc_sigint_handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGINT, &act, NULL);

        close(fds[0]);
        char *line;
        while (1)
        {
            line = readline("> ");
            if (!line)
            {
                printf("minishell: warning: here-document  delimited by end-of-file\n");
                break;
            }
            if (strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
            write(fds[1], line, strlen(line));
            write(fds[1], "\n", 1);
            free(line);
        }
        close(fds[1]);
        exit(0);
    }
    else
    {
        close(fds[1]);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
        {
            close(fds[0]);
            return -2; // SIGINT interrupted heredoc
        }
        return fds[0];
    }
}

int prepare_all_heredocs(t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    while (cmd)
    {
        t_redirection *redir = cmd->redirection;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                int fd = handle_heredoc(redir->file_name);
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