/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:14:57 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/16 10:20:36 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_overflow(long long r, int d, int s)
{
	const long long	mx = 9223372036854775807;
	const long long	mn = (-9223372036854775807 - 1);

	if ((s == 1 && r > (mx - d) / 10) || (s == -1 && (-r) < (mn + d) / 10))
		return (0);
	return (1);
}

static int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-')
		sign = -1;
	if (str[*i] == '+' || str[*i] == '-')
		(*i)++;
	return (sign);
}

int	ft_str_to_ll(const char *str, long long *out)
{
	int			i;
	int			sign;
	long long	res;
	int			dig;

	i = 0;
	res = 0;
	if (!str || !*str)
		return (0);
	sign = parse_sign(str, &i);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		dig = str[i++] - '0';
		if (!check_overflow(res, dig, sign))
			return (0);
		res = res * 10 + dig;
	}
	*out = sign * res;
	return (1);
}

int	get_exit_code(int exit_code)
{
	static int	save;

	if (exit_code != -1)
		save = exit_code;
	return (save);
}

int	get_flag(int flag)
{
	static int	save;

	if (flag != -1)
		save = flag;
	return (flag);
}
