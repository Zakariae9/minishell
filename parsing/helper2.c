#include "../minishell.h"

char	first_quote(char *command)
{
	char	*p_singel;
	char	*p_double;

	p_singel = ft_strchr(command, '\'');
	p_double = ft_strchr(command, '"');
	if (p_singel == NULL && p_double == NULL)
		return ('-');
	if (p_singel != NULL && p_double != NULL)
	{
		if (p_double < p_singel)
			return ('"');
		return ('\'');
	}
	if (p_double == NULL)
		return ('\'');
	return ('"');
}

t_type	witch_type1(char c1)
{
	if (c1 == '>')
		return (en_append);
	else if (c1 == '<')
		return (en_heredoc);
	else if (c1 == '"')
		return (en_double_qoute);
	else if (c1 == '\'')
		return (en_single_qoute);
	else
		return (en_anything_else);

}

t_type	witch_type(char c1, char c2)
{
	if (c1 == c2)
		return (witch_type1(c1));
	if (c1 == '\"')
		return (en_double_qoute);
	else if (c1 == '\'')
		return (en_single_qoute);
	else if (c1 == '|')
		return (en_pip);
	else if (c1 == '>')
		return (en_output);
	else if (c1 == '<')
		return (en_input);
	else
		return (en_word);
}

int	num_of_char(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (c == str[i])
			counter++;
		i++;
	}
	return (counter);
}

char	*ft_getenv(char *var, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var, env->var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
