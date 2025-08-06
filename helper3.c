#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	l;

	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	if (size > src_len)
		l = src_len;
	else
		l = size - 1;
	while (i < l)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	return (ft_strlcpy(dst, src, ft_strlen(src)));
}


char	*delete_spaces(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] != ' ' && str[i] != '	' && str[i])
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
		if (!str[i])
			break ;
		while ((str[i] == ' ' || str[i] == '	') && str[i])
			i++;
		if (j != 0 && str[i])//x=" ls   -l  " if i don't do that x will equal " ls -l" instad of "ls -l"
			new_str[j++] = ' ';
	}
	new_str[j] = 0;
	return (free(str), new_str);
}
int	len_list(t_token *head)
{
	int	counter;

	counter = 0;
	while (head)
	{
		counter++;
		head = head->next;
	}
	return (counter);
}

bool	is_redirection(t_type type)
{
	return (type == en_append || type == en_input 
			|| type == en_output || type == en_heredoc);
}