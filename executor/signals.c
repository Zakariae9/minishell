/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hafi <mel-hafi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 04:14:45 by mel-hafi          #+#    #+#             */
/*   Updated: 2025/08/15 16:17:05 by mel-hafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_sig_s = 0;


int get_exit_code(int exit_code)
{
	static int save;

	if(exit_code != -1)
		save = exit_code;
	return(save);
}

void	set_signals_parent_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_parent_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_quit_handler(int sig)
{
	(void)sig;
	if (g_sig_s)
		write(1, "Quit\n", 5);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_exit_code(130);
}
