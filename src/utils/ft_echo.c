/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:05:06 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/19 18:55:55 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	nb_count(char **av)
{
	int i;

	i = 0;
	while(av[i])
		i++;
	return(i);
}

/*a esta ft del echo tendremos q pasarle los argumentos q se le pasaran,
se ponen en array doble para facilitar na mas*/
int	ft_echo(char **argv)
{
	int	i;
	int n_flag;

	n_flag = 0;
	i = 1;
	if(nb_count(argv) > 1)
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			n_flag = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] == '\0')
				write(1, " ", 1);
			i++;
		}
		
	}
	if(n_flag == 0)
		write(1, "\n", 1);
	return(1);
}
