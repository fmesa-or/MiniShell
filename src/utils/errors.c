/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 18:35:51 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	free_partial_data(data);
	if (data->pwd)
	{
		sfree(data->pwd);
		data->pwd = NULL;
	}
	if (data->home)
	{
		sfree(data->home);
		data->home = NULL;
	}
	if (data->exported_list)
		ft_envclear(&data->exported_list);
}

/***********************************************************************
* This can optionally free all the structure data depending on where   *
* it's called from. Depending on where it's called, something might    *
* need to be freed before the function call.                           *
***********************************************************************/
void	throw_error(const char *str, t_token *tk, t_data *data)
{
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
	if (data)
		free_all_data(data);
	if (tk)
		ft_tokenclear(tk);
	return ;
}
