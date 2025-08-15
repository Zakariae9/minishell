/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:48:22 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/13 11:43:37 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_value(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->var, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*search_cmd_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_value = find_path_value(env);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	full_path = search_cmd_in_paths(paths, cmd);
	free_array(paths);
	return (full_path);
}

char	*join_var_value(const char *var, const char *value)
{
	int		len_var;
	int		len_value;
	char	*result;

	len_var = strlen(var);
	if (!value)
		return (strdup(var));
	len_value = strlen(value);
	result = malloc(len_var + 1 + len_value + 1);
	if (!result)
		return (NULL);
	memcpy(result, var, len_var);
	result[len_var] = '=';
	memcpy(result + len_var + 1, value, len_value);
	result[len_var + 1 + len_value] = '\0';
	return (result);
}

int	fill_env_array(t_env *env, char **array, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (i < count)
	{
		array[i] = join_var_value(tmp->var, tmp->value);
		if (!array[i])
		{
			j = 0;
			while (j < i)
				free(array[j++]);
			free(array);
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}
