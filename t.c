#include "minishell.h"

int	sum(int n)
{
	if (n == 1)
		return n;
	return n + sum(n - 1);
}

int	main()
{
	int	n = sum(5);

	printf("%d\n", n);
	return (0);
}