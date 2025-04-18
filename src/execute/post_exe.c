/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:54:52 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/18 14:35:44 by fmesa-or         ###   ########.fr       */
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
	i--;
	while (i >= 0)
	{
		if (tokens[i].pid > 0)
			kill(tokens[i].pid, SIGKILL);
		i--;
	}
}
/*
*token_prev es el último token
*/
void	ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
	//g_sig = 2 ?????
	//signal_handler(); ?????
	while( waitpid(token_prev->pid, &(token_prev->l_status), 0) > 0)
	{
		data->l_status = token_prev->l_status;
		if (WIFEXITED(token_prev->l_status))
			token_prev->l_status = WEXITSTATUS(token_prev->l_status);
		data->l_status = token_prev->l_status;
	}
	/*aquí Jhon manda el last_token->prev. Es el comando anterior al último
	Lo ideal sería almacenarlo de forma local de algún modo, para no tener que reestructurar todo el trabajo de ramón
	*/
	ms_pilatos(first_token);//kill all children except last one

	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);



/*     V0.1
void	ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
	//g_sig = 2 ?????
	//signal_handler(); ?????
	waitpid(token_prev->pid, &(token_prev->l_status), 0);
	data->l_status = token_prev->l_status;
	if (WIFEXITED(token_prev->l_status))
		token_prev->l_status = WEXITSTATUS(token_prev->l_status);
	data->l_status = token_prev->l_status;
	//aquí Jhon manda el last_token->prev. Es el comando anterior al último
	//Lo ideal sería almacenarlo de forma local de algún modo, para no tener que reestructurar todo el trabajo de ramón

	ms_pilatos(first_token);//kill all children except last one

	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);
	*/
}