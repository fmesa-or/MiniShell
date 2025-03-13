/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:47:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/12/09 16:06:48 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// primer caso, >2 argc da fallo, solo es el exit y el numero
// si solo 2 argc, entoces hace atol al argv [1]


//esto en especifico mira q todo los caracteres de un str son numeros 
int	ft_alldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);

}

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			throw_error("ERROR: ft_atoi fail", NULL, NULL);
		else
			nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb < INT_MIN || nb > INT_MAX)
		throw_error("ERROR: exit number too long", NULL, NULL);
	return ((int) nb);
}

int	ft_exit(char **av)
{
	long	nb;

	write(1, "exit\n", 5);
	if (av[1] && av[2])
	{
		write(1, "bash: exit:", 11);
		write(1, "too many arguments\n", 19);
	}
	if (av[1] && !av[2])
	{
		if (ft_alldigit(av[1]))
		{
			write(1, "bash: exit:", 11);
			write(1, av[1], sizeof(av[1]));
			write(1, ": numeric argument required\n", 29);
		}
		nb = ft_atoi(av[1]);
		//aqui se libera todo
		exit(nb);
	}
	else
		exit(0);
		//arriba de estotambien se libera todo
}
