/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:47:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/22 18:15:22 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// primer caso, >2 argc da fallo, solo es el exit y el numero
// si solo 2 argc, entoces hace atol al argv [1]
// 
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_exit(char **av)
{
	long	nb;
	int		i;
	
	i = 0;
	write(1, "exit", 4);
	if(av[1] && av[2])
		throw_error("ERROR: too many argv for exit");
	if(av[1] && !av[2])
	{
		while (ft_isdigit(av[0][i]))
		{
			//aqui q makina
			i++;
		}
		
		nb = ft_atol(av[1]);
		exit(nb);
	}
	else	
		exit(0);
}
