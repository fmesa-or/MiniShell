/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:54:52 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/27 19:21:43 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
*token_prev es el último token
*/
void ms_post_exe(t_data *data, t_token *token_prev, t_token *first_token)
{
	(void) token_prev;
	(void) first_token;
//	ms_pilatos(first_token);
	sdup2(data->bk_in, STDIN_FILENO);
	sdup2(data->bk_out, STDOUT_FILENO);
}
