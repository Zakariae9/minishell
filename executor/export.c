/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:43:48 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/17 19:48:10 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export(t_env *env)
{
	t_env	**sorted;
	int		i;

	sorted = sort_env(env);
	i = 0;
	while (sorted[i])
	{
		printf("declare -x %s", sorted[i]->var);
		if (sorted[i]->value != NULL)
			printf("=\"%s\"", sorted[i]->value);
		printf("\n");
		i++;
	}
	// free(sorted);
	return (0);
}

void	update_or_append_env(t_env **env, char *name, char *value,
		int has_equal)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->var, name) == 0)
		{
			if (has_equal)
				current->value = value;
			return;
		}
		current = current->next;
	}
	new_node = gc_malloc(en_malloc, sizeof(t_env));
	new_node->var = name;
	new_node->value = value;
	new_node->next = *env;
	*env = new_node;
}

void	add_or_update_env(t_env **env, const char *arg)
{
	char	*equal;
	char	*name;
	char	*value;

	equal = ft_strchr(arg, '=');
	value = NULL;
	if (equal)
	{
		name = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
	}
	else
		name = ft_strdup(arg);
	update_or_append_env(env, name, value, equal != NULL);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	if (!args[1])
		return (print_export(*env));
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, "minishell: export: `", 21);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "`: not a valid identifier\n", 27);
			exit_status = 1;
		}
		else
		{
			add_or_update_env(env, args[i]);
		}
		i++;
	}
	return (exit_status);
}
