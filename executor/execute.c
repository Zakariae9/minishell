/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboumei <zaboumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:26:47 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/13 12:26:30 by zaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_sig_s;

void	wait_for_children(int *pid, int ac, int *exit_status)
{
	int	i;
	int	status;

	i = 0;
	while (i < ac)
	{
		waitpid(pid[i++], &status, 0);
		*exit_status = WEXITSTATUS(status);
	}
	free(pid);
	g_sig_s = 0;
}

void	run_pipeline(t_cmd *cmd, t_env *env, int *pid, int ac)
{
	int		i;
	int		prev_fd;
	int		pipefd[2];
	t_cmd	*head;

	(1) && (i = -1, prev_fd = -1, head = cmd);
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return ((void)(perror("pipe"), cmd->exit_status = 1));
		pid[++i] = fork();
		if (pid[i] == -1)
			return ((void)(perror("fork"), cmd->exit_status = 1));
		if (pid[i] == 0)
			child_process(cmd, env, prev_fd, pipefd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	wait_for_children(pid, ac, &head->exit_status);
}

void	start_pipeline(t_cmd *cmd, t_env *env, int *exit_status)
{
	int		ac;
	t_cmd	*tmp;
	int		*pid;

	ac = 0;
	tmp = cmd;
	g_sig_s = 1;
	while (tmp)
	{
		ac++;
		tmp = tmp->next;
	}
	pid = malloc(sizeof(int) * ac);
	if (!pid)
	{
		perror("malloc");
		*exit_status = 1;
		return ;
	}
	run_pipeline(cmd, env, pid, ac);
}

void	execute_command(t_cmd *cmd, t_env **env, int *exit_status)
{
	int	hd_status;

	hd_status = prepare_all_heredocs(cmd);
	if (hd_status == 130)
		return ((void)(*exit_status = 130));
	if (hd_status != 0)
		return ((void)(*exit_status = 1));
	if (cmd->av && !cmd->next && is_builtin(cmd->av[0]) && is_parent_builtin(cmd->av[0])
		&& !has_redirection(cmd))
	{
		*exit_status = run_builtin(cmd, env);
		return ;
	}
	start_pipeline(cmd, *env, exit_status);
}
