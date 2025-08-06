/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:41:09 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/05 06:34:53 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->var, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	cd_too_many_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		write(2, "cd : too many arguments\n", 24);
		return (1);
	}
	return (0);
}

char	*cd_get_target_path(char **args, t_env **env)
{
	char	*path;

	path = args[1];
	if (!path)
		path = get_env_value(*env, "HOME");
	if (!path)
		write(2, "cd: HOME not set\n", 17);
	return (path);
}

int	cd_update_env(t_env **env, char *oldpwd)
{
	char	*old_line;
	char	*newpwd;
	char	*new_line;

	if (!get_env_value(*env, "PWD"))
		return (0);
	old_line = ft_strjoin("OLDPWD=", oldpwd);
	if (!old_line)
		return (1);
	add_or_update_env(env, old_line);
	free(old_line);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror("cd: getcwd"), 1);
	new_line = ft_strjoin("PWD=", newpwd);
	if (!new_line)
		return (free(newpwd), 1);
	add_or_update_env(env, new_line);
	free(new_line);
	free(newpwd);
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	char	*oldpwd;
	char	*path;
	char	*env_pwd;

	env_pwd = get_env_value(*env, "PWD");
	if (env_pwd)
		oldpwd = ft_strdup(env_pwd);
	else
		oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	if (cd_too_many_args(args))
		return (free(oldpwd), 1);
	path = cd_get_target_path(args, env);
	if (!path)
		return (free(oldpwd), 1);
	if (chdir(path) != 0)
		return (perror("cd"), free(oldpwd), 1);
	if (cd_update_env(env, oldpwd))
		return (free(oldpwd), 1);
	free(oldpwd);
	return (0);
}
