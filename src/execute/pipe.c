/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:21:15 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 10:25:05 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_pipe(t_token *token, t_token *token_prev)
{
	pipe(token->fd)
	if (token_prev)
	{
		token_prev->fd[1] = token->fd[1];
		token_prev->fd[0] = token->fd[0];
	}
}
