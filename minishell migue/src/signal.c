/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumar2 <migumar2@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:43:07 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/17 13:42:48 by migumar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	if (g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	rl_redisplay();
}

void	sigint_handler2(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	signal_quit(int signum)
{
	(void)signum;
	if (g_sig == 1)
		write(1, "Quit (core dumped)\n", 20);
}

void	signal_quit2(int signum)
{
	(void)signum;
	exit(130);
}

void	signal_handler(void)
{
	if (g_sig == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
	}
	else if (g_sig == 1)
	{
		signal(SIGQUIT, signal_quit);
		signal(SIGINT, signal_quit2);
	}
	if (g_sig == 2)
	{
		signal(SIGINT, sigint_handler2);
		signal(SIGQUIT, SIG_IGN);
	}
}
