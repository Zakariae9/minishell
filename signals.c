#include"minishell.h"

int sig_s = 0;
void	sigint_handler(int sig)
{

	if (!sig_s)
	{
		(void)sig;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);  // Ctrl-C
	signal(SIGQUIT, SIG_IGN);        // 
}