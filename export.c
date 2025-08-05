/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:43:48 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/03 06:04:12 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env **sort_env(t_env *env)
{
    int size = 0;
    t_env *tmp = env;
    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }

    t_env **array = malloc(sizeof(t_env *) * (size + 1));
    if (!array)
        return NULL;

    tmp = env;
    for (int i = 0; i < size; i++)
    {
        array[i] = tmp;
        tmp = tmp->next;
    }
    array[size] = NULL;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (ft_strcmp(array[i]->var, array[j]->var) > 0)
            {
                t_env *swap = array[i];
                array[i] = array[j];
                array[j] = swap;
            }
        }
    }
    return array;
}



int is_valid_identifier(const char *arg)
{
    int i = 0;

    if (!arg || !(ft_isalpha(arg[0]) || arg[0] == '_'))
        return 0;

    while (arg[i] && arg[i] != '=')
    {
        if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}


int print_export(t_env *env)
{
    t_env **sorted = sort_env(env);
    int i = 0;

    while (sorted[i])
    {
        write(STDOUT_FILENO, "declare -x ", 11);
        write(STDOUT_FILENO, sorted[i]->var, ft_strlen(sorted[i]->var));
        if (sorted[i]->value != NULL)
        {
            write(STDOUT_FILENO, "=\"", 2);
            write(STDOUT_FILENO, sorted[i]->value, ft_strlen(sorted[i]->value));
            write(STDOUT_FILENO, "\"", 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
    free(sorted);
    return 0;
}





void add_or_update_env(t_env **env, const char *arg)
{
    char *equal = ft_strchr(arg, '=');
    char *name;
    char *value = NULL;

    if (equal)
    {
        name = ft_substr(arg, 0, equal - arg);
        value = ft_strdup(equal + 1);
    }
    else
        name = ft_strdup(arg);

    t_env *current = *env;
    while (current)
    {
        if (ft_strcmp(current->var, name) == 0)
        {
            free(current->value);
            current->value = value;
            free(name);
            return;
        }
        current = current->next;
    }

    // add new node
    t_env *new_node = malloc(sizeof(t_env));
    new_node->var = name;
    new_node->value = value;
    new_node->next = *env;
    *env = new_node;
}





// ----------- Main Export Function -----------

int ft_export(char **args, t_env **env)
{
    int i = 1;

    if (!args[1])
        return print_export(*env);

    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            
            write(2, "minishell: export: `", 21);
            write(2, args[i], ft_strlen(args[i]));
            write(2, "`: not a valid identifier\n", 27);
        }
        else
        {
            add_or_update_env(env, args[i]);
        }
        i++;
    }
    return 0;
}
