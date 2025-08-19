/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:26:47 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/18 18:13:38 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_children(int *pid, int ac)
{
	int	i;
	int	status;
	int	sig;
	int	printed_newline;

	printed_newline = 0;
	i = -1;
	while (++i < ac && waitpid(pid[i], &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT && !printed_newline++)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				write(1, "Quit\n", 5);
			get_exit_code(128 + sig);
		}
		else
			get_exit_code(WEXITSTATUS(status));
	}
	get_flag(0);
	set_signals_parent_interactive();
}

int	fork_and_exec_cmd(t_cmd *cmd, t_env *env, int prev_fd, int pipefd[2])
{
	pid_t	pid;

	if (cmd->next && pipe(pipefd) == -1)
	{
		perror("pipe");
		get_exit_code(1);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		get_exit_code(1);
		return (-1);
	}
	if (pid == 0)
	{
		set_signals_child_default();
		child_process(cmd, env, prev_fd, pipefd);
	}
	return (pid);
}

void	run_pipeline(t_cmd *cmd, t_env *env, int *pid, int ac)
{
	int		i;
	int		prev_fd;
	int		pipefd[2];
	t_cmd	*head;

	i = 0;
	prev_fd = -1;
	head = cmd;
	while (cmd)
	{
		pid[i] = fork_and_exec_cmd(cmd, env, prev_fd, pipefd);
		if (pid[i] == -1)
			return ;
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
		i++;
	}
	set_signals_parent_ignore();
	wait_for_children(pid, ac);
}

void	start_pipeline(t_cmd *cmd, t_env *env)
{
	int		ac;
	t_cmd	*tmp;
	int		*pid;

	ac = 0;
	tmp = cmd;
	get_flag(1);
	while (tmp)
	{
		ac++;
		tmp = tmp->next;
	}
	pid = gc_malloc(en_malloc, sizeof(int) * ac);
	if (!pid)
	{
		perror("malloc");
		get_exit_code(1);
		return ;
	}
	run_pipeline(cmd, env, pid, ac);
}

void	execute_command(t_cmd *cmd, t_env **env)
{
	int	hd_status;

	hd_status = prepare_all_heredocs(cmd, *env);
	if (hd_status == 130)
	{
		get_exit_code(130);
		return ;
	}
	if (hd_status != 0)
	{
		get_exit_code(1);
		return ;
	}
	if (cmd->av && !cmd->next && is_parent_builtin(cmd->av[0])
		&& !has_redirection(cmd))
	{
		get_exit_code(run_builtin(cmd, env));
		return ;
	}
	start_pipeline(cmd, *env);
}
