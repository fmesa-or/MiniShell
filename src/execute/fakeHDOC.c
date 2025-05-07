/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fakeHDOC.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:53:19 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/07 14:13:03 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fake_hdoc(t_token *token)
{
	char	*line;
	pid_t	reader;

	reader = fork();
	if (reader == 0)
	{	setup_signal_handlers_hd();
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, token->redir->file) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	else
		waitpid(reader, NULL, 0);
}
