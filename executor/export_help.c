/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:43:51 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/16 13:33:52 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_env_array(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*swap;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(array[i]->var, array[j]->var) > 0)
			{
				swap = array[i];
				array[i] = array[j];
				array[j] = swap;
			}
			j++;
		}
		i++;
	}
}

t_env	**sort_env(t_env *env)
{
	int		size;
	int		i;
	t_env	*tmp;
	t_env	**array;

	size = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	array = gc_malloc(en_malloc, sizeof(t_env *) * (size + 1));
	if (!array)
		return (NULL);
	tmp = env;
	while (i < size)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	array[size] = NULL;
	sort_env_array(array, size);
	return (array);
}

int	is_valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || !(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
