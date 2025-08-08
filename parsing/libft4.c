#include "../minishell.h"

char	*add_str(char *old_str, char *added_str, int pos)
{
	int		i_old_str;
	int		i_added_str;
	int		i_new_str;
	int		len_added_str;
	char	*new_str;

	i_old_str = 0;
	i_added_str = 0;
	i_new_str = 0;
	len_added_str = ft_strlen(added_str);
	new_str = malloc(len_added_str + ft_strlen(old_str) + 1);
	if (new_str == NULL)
		return (NULL);
	if (pos == 0)
		return (ft_strjoin(added_str, old_str));
	while (i_old_str < pos)
		new_str[i_new_str++] = old_str[i_old_str++];
	while (i_added_str < len_added_str)
		new_str[i_new_str++] = added_str[i_added_str++];
	while (old_str[i_old_str])
		new_str[i_new_str++] = old_str[i_old_str++];
	new_str[i_new_str] = 0;
		return (new_str);
}

char	*delete_part(char *old_str, char *deleted_str)
{
	int		len_new_str;
	int		len_deleted_str;
	int		len_old_str;
	int		i_new_str;
	int		i_old_str;
	char	*new_str;
	char	*temp;

	i_new_str = 0;
	i_old_str = 0;
	len_deleted_str = ft_strlen(deleted_str);
	len_old_str = ft_strlen(old_str);
	len_new_str = ft_strlen(old_str) - len_deleted_str;
	new_str = malloc(len_new_str + 1);
	if (new_str == NULL)
		return (NULL);
	temp = old_str;
	deleted_str = ft_strnstr(old_str, deleted_str, len_old_str);
	while (temp++ != deleted_str)
		new_str[i_new_str++] = old_str[i_old_str++];
	i_old_str += len_deleted_str;
	while (old_str[i_old_str])
		new_str[i_new_str++] = old_str[i_old_str++];
	new_str[i_new_str] = 0;
	return (new_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		counter++;
		s++;
	}
	return (counter);
}
