<<<<<<< HEAD
/******************************************************************************/
=======
/* ************************************************************************** */
>>>>>>> export
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/10/02 19:16:07 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	throw_error(const char *str)
{
	perror(str);
	exit (errno);
}
=======
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/12/05 15:54:15 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* esto opcionalmente puede liberar todo lo de las estructuras pa segun donde se llame
	Puede que segun donde se llame, a lo mejor hay que liberar algo antes de la llamada */
void	throw_error(const char *str, t_token *tk, t_data *data)
{
	write (1, str, sizeof(str));
	if (data)
		free_all_data(data);
	if (tk)
		ft_tokenclear(tk);
	exit (errno);
}


>>>>>>> export
