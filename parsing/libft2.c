#include "../minishell.h"

void	fill_str(char const *str1, char const *str2, char *buffer)
{
	int	i;

	i = 0;
	while (str1[i])
	{
		*buffer = str1[i];
		i++;
		buffer++;
	}
	i = 0;
	while (str2[i])
	{
		*buffer = str2[i];
		buffer++;
		i++;
	}
	*buffer = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = malloc(len);
	if (new_str == NULL)
		return (NULL);
	fill_str(s1, s2, new_str);
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	is_there_here(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strchr(const char *s, int c)
{
	int	is_there;

	is_there = is_there_here(s, c);
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	if (is_there == -1)
		return (NULL);
	return ((char *)(s + is_there));
}
