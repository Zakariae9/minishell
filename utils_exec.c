/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:48:22 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/07/23 04:12:52 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *find_cmd_path(char *cmd, t_env *env)
{
    char *path_value = NULL;
    char **paths = NULL;
    char *full_path = NULL;
    int i;

    // ila lcommand fih '/' dir exécute direct
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
            return ft_strdup(cmd);
        else
            return NULL;
    }

    // cherche 3la PATH f env
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

    // split PATH b ':'
    paths = ft_split(path_value, ':');
    if (!paths)
        return NULL;

    // dwiro 3la kol path, zayd command, w chof access
    i = 0;
    while (paths[i])
    {
        char *tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);

        if (full_path && access(full_path, X_OK) == 0)
        {
            free_array(paths);
            return full_path;
        }
        free(full_path);
        i++;
    }

    free_array(paths);
    return NULL;
}



static char *join_var_value(const char *var, const char *value)
{
    size_t len_var = strlen(var);
    if (!value)
        return strdup(var);
    size_t len_value = strlen(value);
    char *result = malloc(len_var + 1 + len_value + 1); // var + '=' + value + '\0'
    if (!result)
        return NULL;
    memcpy(result, var, len_var);
    result[len_var] = '=';
    memcpy(result + len_var + 1, value, len_value);
    result[len_var + 1 + len_value] = '\0';
    return result;
}

char **convert_env_to_array(t_env *env)
{
    size_t count = 0;
    t_env *tmp = env;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    char **array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return NULL;

    tmp = env;
    for (size_t i = 0; i < count; i++)
    {
        array[i] = join_var_value(tmp->var, tmp->value);
        if (!array[i])
        {
            // Free previously allocated strings and array on failure
            for (size_t j = 0; j < i; j++)
                free(array[j]);
            free(array);
            return NULL;
        }
        tmp = tmp->next;
    }
    array[count] = NULL; // NULL-terminate the array
    return array;
}

