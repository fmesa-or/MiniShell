/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fakeHDOC.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:53:19 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 21:10:53 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fake_hdoc(t_token *token, t_data *data)
{
	char	*line;
	pid_t	reader;

	reader = fork();
	if (reader == 0)
	{
		setup_signal_handlers_hd();
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, token->redir->file) == 0)
			{
				sfree(line, data);
				break ;
			}
			sfree(line, data);
		}
	}
	else
		waitpid(reader, NULL, 0);
}
