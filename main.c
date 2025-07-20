#include "minishell.h"

void	read_commands(t_token	**head, t_env *env_head)
{
	char	*command;

	*head = NULL;
	command	 = readline("minishell> ");
	add_history(command);
	if (check_are_qoutes_open(command))
	{
		ft_putstr_fd("syntax error\n", 2);
		return ;
	}
	lexer(command, head);
	if (!(*head))
		return ;
	if (!are_bash_rules_correct(*head))
	{
		ft_putstr_fd("Fail\n", 2);
		return free_list_tokens(head);
	}
	else
		expanding_all_tokens(*head, env_head);
	fixing_tokens(*head);
}

void	start_minishell(char **env)
{
	t_token		*head;
	t_env		*head_env;
	t_cmd		*cmd;
	int		g_exit_status = 0;


	make_env_list(env, &head_env);
	while (1)
	{
		read_commands(&head, head_env);
		if (!head)
			continue ;
		//print_tokens(head);
		merging(head, &cmd);
		printf("%s\n", cmd->av[0]);
		if(cmd)
		{
			execute_command(cmd , &head_env , &g_exit_status);
			free_cmd_list(cmd);
		}
		free_list_tokens(&head);
	}
}


int	main(int ac, char **av, char **env)
{
	if (ac > 1 || av[1])
		return (1);
	start_minishell(env);
	
	return (0);
}
