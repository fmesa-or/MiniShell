/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:54:52 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/01 12:45:13 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern int	g_sig;  ??????

static void	ms_pilatos(t_token *tokens)
{
	int	i;

	i = 0;
	while(tokens[i].type != NONE)
		i++;
	i = i - 2;
	while (i >= 0)
	{
		if (tokens[i].pid >0)
			kill(tokens[i].pid, SIGKILL);
		i--;
	}
}

void	ms_post_exe(t_data *data, t_token *last_token, t_token *first_token)
{
	//g_sig = 2 ?????
	//signal_handler(); ?????

	//Se queda atascado en el waitpid
	waitpid(last_token->pid, &(last_token->l_status), 0);

	//		printf(PR"POST EXE\n"RES);
	data->l_status = last_token->l_status;
	if (WIFEXITED(last_token->l_status))
		last_token->l_status = WEXITSTATUS(last_token->l_status);
	data->l_status = last_token->l_status;
	ms_pilatos(first_token);//kill all children except last one
	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);
}

//ls | wc -l | wc -l