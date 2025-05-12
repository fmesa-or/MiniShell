/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/12 13:04:05 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* esto opcionalmente puede liberar todo lo de las estructuras pa segun donde se llame
	Puede que segun donde se llame, a lo mejor hay que liberar algo antes de la llamada */
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
