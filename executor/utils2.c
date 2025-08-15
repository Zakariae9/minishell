/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:50:18 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/14 08:52:54 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_redirection(t_cmd *cmd)
{
	return (cmd->redirection != NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*s;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		start++;
	}
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		end--;
	}
	s = malloc(end - start + 1);
	if (!s)
		return (NULL);
	while (start < end)
		s[i++] = s1[start++];
	s[i] = '\0';
	return (s);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	print_error_exit(char *msg, char *arg, int code)
{
	if (arg)
		write(2, arg, ft_strlen(arg));
	write(2, msg, ft_strlen(msg));
	exit(code);
}

char	**convert_env_to_array(t_env *env)
{
	int		count;
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
