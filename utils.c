#include "minishell.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
char	*ft_strcpyy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
	}
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
int has_redirection(t_cmd *cmd)
{
    return (cmd->redirection != NULL);
}