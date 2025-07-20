/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:48:22 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/07/19 16:37:07 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *find_cmd_path(char *cmd, t_env *env)
{
    char *path_value = NULL;
    char **paths = NULL;
    char *full_path = NULL;
    int i;

    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        else
            return NULL;
    }
    while (env)
    {
        if (ft_strcmp(env->var, "PATH") == 0)
        {
            path_value = env->value;
            break;
        }
        env = env->next;
    }

    if (!path_value)
        return NULL;

    paths = ft_split(path_value, ':');
    if (!paths)
        return NULL;

    i = 0;
    while (paths[i])
    {
        full_path = join_path(paths[i], cmd);
        if (full_path)
        {
            if (access(full_path, X_OK) == 0)
            {
                free_array(paths);
                return full_path;
            }
            free(full_path);
        }
        i++;
    }
    free_array(paths);
    return NULL;
}


char *join_path(const char *dir , const char *cmd)
{
    char *full_path;
    size_t len_dir = ft_strlen(dir);
    size_t len_cmd = ft_strlen(cmd);

    full_path = malloc(len_cmd + len_dir + 2);
    if(!full_path)
        return(NULL);
    ft_strcpy(full_path , dir); 
    ft_strcat(full_path, "/");
    ft_strcat(full_path , cmd);
    return(full_path);
}

char **convert_env_to_array(t_env *env)
{
	int i = 0;
	t_env *tmp = env;
	char **array;
	

	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}

	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return NULL;

	tmp = env;
	i = 0;
	while (tmp)
	{
		array[i] = malloc(ft_strlen(tmp->value) + ft_strlen(tmp->value) + 2);
		if (!array[i])
			return NULL;
		ft_strcpy(array[i], tmp->value);
		ft_strcat(array[i], "=");
		ft_strcat(array[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return array;
}
