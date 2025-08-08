/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboumei <zaboumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:42:54 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/07 11:02:50 by zaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
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
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	newline;
	int	j;

	i = 1;
	newline = 1;
	while (cmd->av[i] && ft_strncmp(cmd->av[i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->av[i][j] == 'n')
			j++;
		if (cmd->av[i][j] != '\0')
			break ;
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
	if(newline)
		return (write(1, "\n", 1), 0);
	return 0;
}

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **av)
{
	long long	code;

	printf("exit\n");
	if (av[1])
	{
		if (!is_numeric(av[1]) || !ft_str_to_ll(av[1], &code))
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
				av[1]);
			exit(2);
		}
		if (av[2])
		{
			fprintf(stderr, "minishell: exit: too many arguments\n");
			return ;
		}
		exit((unsigned char)code);
	}
	exit(0);
}
