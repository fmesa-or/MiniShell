/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:21:15 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/30 08:41:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_pipe(t_token *token)
{
	printf("\n\tPIPE: %d\n\n", pipe(token[1].fd));
	if (token)
	{
		token->fd[1] = token[1].fd[1];
		token->fd[0] = token[1].fd[0];
	}
}
