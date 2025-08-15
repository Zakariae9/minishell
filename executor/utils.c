/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:14:02 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/13 10:51:40 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(const char *s, char c)
{
	int	i;
	int	count;
	int	word;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && word == 0)
		{
			count++;
			word = 1;
		}
		else if (s[i] == c)
		{
			word = 0;
		}
		i++;
	}
	return (count);
}

int	len_word(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*allocate_word(const char *s, int len)
{
	char	*word;
	int		i;

	if (!s || len < 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_split(char **arr, int index)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (i < index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		words;
	int		j;
	int		lenw;

	if (!s)
		return (NULL);
	words = count_word(s, c);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	j = 0;
	while (*s && j < words)
	{
		while (*s && *s == c)
			s++;
		lenw = len_word(s, c);
		str[j] = allocate_word(s, lenw);
		if (!str[j])
			return (free_split(str, j));
		s += lenw;
		j++;
	}
	str[j] = NULL;
	return (str);
}
