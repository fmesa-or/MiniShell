/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:09:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 14:40:25 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	ctrl_c_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_quit_handler(int sig)
{
	(void)sig;
	rl_redisplay();
}

/*   V0.1
void	ctrl_c_handler_hd(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
//	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(1);
}
*/

void	setup_signal_handlers(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
}
