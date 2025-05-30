/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:13:15 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 20:03:28 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_fds(t_token *token, t_token *token_prev, int *fd)
{
	if (token->redir)
		token->l_status = ms_init_redir(token, fd, token_prev);
	if (token[1].type != NONE)
	{
		if (spipe(fd) == -1)
		{
			perror("pipe");
			sexit(EXIT_FAILURE);
		}
	}
}
