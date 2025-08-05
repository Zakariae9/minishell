/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:42:54 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/03 06:23:31 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			write(1, env->var, ft_strlen(env->var));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return 0;
}

int ft_echo(t_cmd *cmd)
{
    int i = 1;
    int newline = 1;

    while (cmd->av[i] && ft_strncmp(cmd->av[i], "-n", 2) == 0)
    {
        int j = 2;
        while (cmd->av[i][j] == 'n')
            j++;
        if (cmd->av[i][j] != '\0')
            break;
        newline = 0;
        i++;
    }
    while (cmd->av[i])
    {
        write(1, cmd->av[i], ft_strlen(cmd->av[i]));
        if (cmd->av[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline == 1)
        write(1, "\n", 1);
    return(0);
}

int ft_pwd(void)
{
    char pwd[1024];
    
    if(getcwd(pwd,sizeof(pwd)) != NULL)
    {
        printf("%s\n" , pwd);
        return 0;
    }
    else
    {
        perror("pwd");
        return(1);
    }
}

int is_numeric(const char *str)
{
    if (!str || !*str)
        return 0;
    int i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    for (; str[i]; i++)
        if (!isdigit((unsigned char)str[i]))
            return 0;
    return 1;
}

void ft_exit(char **av)
{
    printf("exit\n");
    if (av[1])
    {
        if (!is_numeric(av[1]))
        {
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", av[1]);
            exit(255);
        }
        else if (av[2])
        {
            fprintf(stderr, "minishell: exit: too many arguments\n");
            return;
        }
        else
            exit(atoi(av[1]));
    }
    exit(0);
}
