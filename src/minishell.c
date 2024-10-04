/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/04 16:18:53 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	
	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1 && argv)
	{
		t_list *list =envtolist(env);
		ft_pwd(list);
	}
	return (0);
}

//Tienes segmentation fault
//Hay que comprobar todo lo que vamos haciendo