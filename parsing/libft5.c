#include "../minishell.h"

static size_t	int_len(long n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	fill(long n, char *s, size_t len)
{
	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		n = -1 * n;
	}
	while (len-- > 0)
	{
		if (s[len] == '-')
			return ;
		s[len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str_nbr;
	size_t	len;
	long	num;

	num = n;
	len = int_len(num);
	str_nbr = gc_malloc(en_malloc, len + 1);
	if (str_nbr == NULL)
		return (NULL);
	fill(n, str_nbr, len);
	return (str_nbr);
}
