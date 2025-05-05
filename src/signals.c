/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:09:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/05 13:13:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal;

void	ctrl_c_handler(int sig)
{
	(void)sig;
	dprintf(2, RD"cntrl+C\n"RES);
	g_signal = SIGINT;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	ctrl_quit_handler(int sig)
{
	(void)sig;
	dprintf(2, RD"cntrl+barra\n"RES);
	rl_redisplay();
}
void	ctrl_quit_handler_hd(int sig)
{
	(void)sig;
}
void	ctrl_c_handler_hd(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(1);
}
void setup_signal_handlers(void)
{
	dprintf(2, "HEMOS LLEGADO\n");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
}
void setup_signal_handlers_hd(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler_hd);
}