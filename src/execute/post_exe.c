/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:54:52 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 20:40:40 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern int	g_sig;
/*
static void ms_pilatos(t_token *tokens)
{
	int i;

	i = 0;
	// Encontrar el último token
	while (tokens[i].type != NONE)
		i++;
	i--;

	// Matar todos los procesos hijos excepto el último
	while (i >= 0)
	{
		if (tokens[i].pid > 0)
		{
			dprintf(2, "Matando proceso hijo PID: %d\n", tokens[i].pid);
			kill(tokens[i].pid, SIGKILL);
		}
		i--;
	}
}*/

/*
*token_prev es el último token
*/
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
	(void) token_prev;
	(void) first_token;
//	ms_pilatos(first_token);
	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);
}
