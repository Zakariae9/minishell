/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:41:09 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/07/15 08:41:29 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *get_env_value(t_env *env, const char *name)
{
    while (env)
    {
        if (ft_strcmp(env->var, name) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

int ft_cd(char **args, t_env **env)
{
    char *oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (perror("cd: getcwd"), 1);

    // destination path
    char *path = args[1];
    if (!path)
        path = get_env_value(*env, "HOME");
    if (!path)
    {
        free(oldpwd);
        write(2, "cd: HOME not set\n", 17);
        return 1;
    }

    // change directory
    if (chdir(path) != 0)
    {
        perror("cd");
        free(oldpwd);
        return 1;
    }

    // update OLDPWD
    char *old_line = ft_strjoin("OLDPWD=", oldpwd);
    add_or_update_env(env, old_line);
    free(old_line);
    free(oldpwd);

    // update PWD
    char *newpwd = getcwd(NULL, 0);
    if (!newpwd)
        return (perror("cd: getcwd"), 1);
    char *new_line = ft_strjoin("PWD=", newpwd);
    add_or_update_env(env, new_line);
    free(new_line);
    free(newpwd);

    return 0;
}
