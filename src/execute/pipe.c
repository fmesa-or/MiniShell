/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:21:15 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/09 13:18:23 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe(t_token *token, t_token *token_prev)
{
	printf("PIPE init\n");
	pipe(token->fd);
	//if (token_prev)
		token->fd[0] = token_prev->fd[1];
	//if (token[1].type != NONE)
		token[1].fd[0] = token->fd[1];
}
