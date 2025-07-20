#include"minishell.h"

// int ft_strcmp(const char *s1, const char *s2)
// {
//     int i = 0;

//     while (s1[i] && s2[i] && s1[i] == s2[i])
//         i++;

//     return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

// size_t ft_strlen(const char *s)
// {
//     size_t i = 0;
//     while (s[i])
//         i++;
//     return i;
// }
// char *ft_strstr(const char *haystack, const char *needle)
// {
//     if (!*needle)
//         return (char *)haystack;

//     while (*haystack)
//     {
//         const char *h = haystack;
//         const char *n = needle;

//         while (*h && *n && *h == *n)
//         {
//             h++;
//             n++;
//         }

//         if (*n == '\0')
//             return (char *)haystack;

//         haystack++;
//     }

//     return NULL;
// }

// char *ft_strdup(const char *s)
// {
//     //    printf("🧪 ft_strdup called with: [%s]\n", s);
//     int i = 0;
//     char *copy;

//     while (s[i])
//         i++;

//     copy = malloc(sizeof(char) * (i + 1));
//     if (!copy)
//         return NULL;

//     for (int j = 0; j <= i; j++) 
//         copy[j] = s[j];

//     return copy;
// }

// char *ft_strchr(const char *s, int c)
// {
//     while (*s)
//     {
//         if (*s == (char)c)
//             return (char *)s;
//         s++;
//     }
//     if (*s == (char)c)
//         return (char *)s;
    
//     return NULL;
// }
void	ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
void ft_putchar(char c)
{
    write(1,&c,1);
}
char *ft_strcpyy(char *dest, const char *src)
{
    int i = 0;
    
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

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
    return dest;
}

// int ft_strncmp(const char *str1, const char *str2, size_t n)
// {
//     size_t i = 0;

//     while (i < n && str1[i] != '\0' && str2[i] != '\0')
//     {
//         if (str1[i] != str2[i])
//             return (unsigned char)str1[i] - (unsigned char)str2[i]; // Return difference if characters don't match
//         i++;
//     }
//     if (i < n)
//         return (unsigned char)str1[i] - (unsigned char)str2[i];  // Return the difference at the nth character (or end of string)

//     return 0;
// }
void free_env_list(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
	}
}
void free_array(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

// int ft_isalpha(int c)
// {
//     return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
// }
// int ft_isalnum(int c)
// {
//     return (ft_isalpha(c) || (c >= '0' && c <= '9'));
// }


// char *ft_substr(const char *s, unsigned int start, size_t len)
// {
//     size_t i = 0;
//     size_t s_len = ft_strlen(s);
//     char *substr;

//     if (!s || start >= s_len)
//         return ft_strdup("");

//     if (len > s_len - start)
//         len = s_len - start;

//     substr = malloc(len + 1);
//     if (!substr)
//         return NULL;

//     while (i < len && s[start + i])
//     {
//         substr[i] = s[start + i];
//         i++;
//     }
//     substr[i] = '\0';

//     return substr;
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	len1 = ft_strlen(s1);
// 	size_t	len2 = ft_strlen(s2);
// 	char	*result = malloc(len1 + len2 + 1);
// 	size_t	i = 0, j = 0;

// 	if (!result)
// 		return (NULL);
// 	while (s1 && s1[i])
// 	{
// 		result[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j])
// 	{
// 		result[i + j] = s2[j];
// 		j++;
// 	}
// 	result[i + j] = '\0';
// 	return (result);
// }
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