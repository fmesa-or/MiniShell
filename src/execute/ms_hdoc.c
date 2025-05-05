/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:49 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/05 14:33:24 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_hdoc_writer(int *fd, char *line, char *limiter)
{
	if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		write(1, "> ", 2);
	else if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS); //revisar
	write(fd[1], line, ft_strlen(line));
}

/*************************************************************************
*1st:	Starts the pipe.                                                 *
*2nd:	Starts the child process.                                        *
*3rd:	Read from the STDIN with GNL until it finds the limiter.         *
*************************************************************************/
void	ms_here_doc(t_token *token, t_data *data, int *fd)
{
	pid_t	reader;
	char	*line;

	if (pipe(fd) == -1)
		throw_error("Error: Pipe not working.", token, data);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		write(1, "> ", 2);
		setup_signal_handlers_hd();
		while (ms_gnl(&line))
			ms_hdoc_writer(fd, line, token->redir->file);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
}