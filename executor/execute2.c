/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:22:56 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/06 09:32:06 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_executable_validity(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", path);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		perror(path);
		free(path);
		exit(126);
	}
}

char	*resolve_executable_path_or_exit(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (!cmd->av[0] || !*cmd->av[0])
		return (fprintf(stderr, "Command '' not found\n"), exit(127), NULL);
	if (ft_strchr(cmd->av[0], '/'))
	{
		if (access(cmd->av[0], F_OK) != 0)
			return (fprintf(stderr, "%s: No such file or directory\n",
					cmd->av[0]), exit(127), NULL);
		path = ft_strdup(cmd->av[0]);
	}
	else
	{
		path = find_cmd_path(cmd->av[0], env);
		if (!path)
			return (fprintf(stderr, "%s: command not found\n", cmd->av[0]),
				exit(127), NULL);
	}
	check_executable_validity(path);
	return (path);
}

void	run_execve(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	path = resolve_executable_path_or_exit(cmd, env);
	envp = convert_env_to_array(env);
	execve(path, cmd->av, envp);
	perror("execve");
	free(path);
	free_array(envp);
	exit(126);
}

void	child_process(t_cmd *cmd, t_env *env, int prev_fd, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (handle_redirections(cmd->redirection) != 0)
	{
		exit(1);
	}
	if (is_builtin(cmd->av[0]))
		exit(run_builtin(cmd, &env));
	run_execve(cmd, env);
}

char	**convert_env_to_array(t_env *env)
{
	size_t	count;
	t_env	*tmp;
	char	**array;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	if (fill_env_array(env, array, count))
		return (NULL);
	array[count] = NULL;
	return (array);
}
