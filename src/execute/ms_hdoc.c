/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:52:49 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/07 14:06:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_hdoc_writer(int *fd, char *line, char *limiter)
{
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	exit(EXIT_SUCCESS);
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

	line = NULL;
	if (pipe(fd) == -1)
		throw_error("Error: Pipe not working.", token, data);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		setup_signal_handlers_hd();
		ms_hdoc_writer(fd, line, token->redir->file);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
}
