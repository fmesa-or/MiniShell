/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/10/01 17:53:13 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"
#include <errno.h>

void	throw_error(const char *str)
{
	perror(str);
	exit (errno);
}