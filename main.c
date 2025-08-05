#include "minishell.h"

void	read_commands(char *input ,t_token	**head, t_env *env_head)
{

	*head = NULL;

	if (check_are_qoutes_open(input))
	{
		ft_putstr_fd("syntax error\n", 2);
		return ;
	}
	lexer(input, head);
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


	make_env_list(env, &head_env);
	t_env **envp = &head_env;
	while (1)
	{
		setup_signals();
		char *input = readline("minishell> ");
		if(!input)
		{
			write(1 ,"exit\n" , 5);
			rl_clear_history();
			break;
		}
		if(*input)
			add_history(input);
		read_commands(input , &head , head_env);
		free(input);
		if (!head)
			continue ;
		merging(head, &cmd);

		cmd->exit_status = 0;
		if(cmd)
		{
			execute_command(cmd , envp , &cmd->exit_status);
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
