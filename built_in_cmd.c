/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:41:15 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/07/15 08:43:13 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_parent_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0
        || ft_strcmp(cmd, "exit") == 0);
}

bool is_builtin(char *cmd)
{
    const char *builtind[] = {"cd" , "echo" , "pwd" , "exit" ,"export", "unset", "env", NULL};

    int i = 0;
    if(!cmd)
        return false;
    while(builtind[i])
    {
        if(ft_strcmp(cmd , builtind[i]) == 0)
            return true;
        i++;
    }
    return false;
}

int run_builtin(t_cmd *cmd, t_env **env)
{
     if (ft_strcmp(cmd->av[0], "cd") == 0)
         return ft_cd(cmd->av, env);
    else if (ft_strcmp(cmd->av[0], "echo") == 0)
        return ft_echo(cmd);
    else if (ft_strcmp(cmd->av[0], "pwd") == 0)
        return ft_pwd();
    else if (ft_strcmp(cmd->av[0], "exit") == 0)
        ft_exit(cmd->av);
    else if (ft_strcmp(cmd->av[0], "export") == 0)
        return ft_export(cmd->av, env);                    
    else if (ft_strcmp(cmd->av[0], "unset") == 0)
        return ft_unset(env, cmd->av);
    else if (ft_strcmp(cmd->av[0], "env") == 0)
        return ft_env(*env);
    return 1;
}





