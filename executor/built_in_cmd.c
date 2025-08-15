/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:41:15 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/11 06:45:32 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_parent_builtin(char *cmd)
{
	const char	*builtind[] = {"cd", "exit", "export", "unset", NULL};
	int			i;

	i = 0;
	if (!cmd)
		return (0);
	while (builtind[i])
	{
		if (ft_strcmp(cmd, builtind[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	const char	*builtind[] = {"cd", "echo", "pwd", "exit", "export", "unset",
		"env", NULL};
	int			i;

	i = 0;
	if (!cmd)
		return (0);
	while (builtind[i])
	{
		if (ft_strcmp(cmd, builtind[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	run_builtin(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->av[0], "cd") == 0)
		return (ft_cd(cmd->av, env));
	else if (ft_strcmp(cmd->av[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->av[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->av[0], "exit") == 0)
		ft_exit(cmd->av);
	else if (ft_strcmp(cmd->av[0], "export") == 0)
		return (ft_export(cmd->av, env));
	else if (ft_strcmp(cmd->av[0], "unset") == 0)
		return (ft_unset(env, cmd->av));
	else if (ft_strcmp(cmd->av[0], "env") == 0)
		return (ft_env(*env));
	return (1);
}
