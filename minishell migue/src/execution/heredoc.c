/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:02:09 by jholland          #+#    #+#             */
/*   Updated: 2024/07/17 14:05:41 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_sig;

static void	heredoc_loop(char *eof, int fd_write)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

static void	heredoc_hint(char *eof)
{
	write(1, "-HEREDOC- Expecting \"", 22);
	write(1, eof, ft_strlen(eof));
	write(1, "\">\n", 3);
}

int	create_heredoc(char *eof)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		g_sig = 1;
		signal_handler();
		heredoc_hint(eof);
		heredoc_loop(eof, fd[1]);
		exit(0);
	}
	else
	{
		g_sig = 0;
		signal_handler();
		waitpid(pid, &status, 0);
		close(fd[1]);
	}
	g_sig = 2;
	signal_handler();
	return (fd[0]);
}
