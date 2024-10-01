/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/01 18:10:30 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1)
		throw_error("ERROR: ");
	return (0);
}
