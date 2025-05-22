/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:47:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/21 21:10:44 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_alldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
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

int	bi_exit(char **av)
{
	long	nb;

//	write(1, "exit\n", 5);
	if (av[1] && av[2])
	{
		write(1, "minishell: exit:", 11);
		write(1, "too many arguments\n", 19);
		return (1);
	}
	else if (av[1] && !av[2])
	{
		if (ft_alldigit(av[1]) == 0)
		{
			write(1, "minishell: exit: ", 12);
			write(1, av[1], sizeof(av[1]));
			write(1, ": numeric argument required\n", 29);
			sexit(2);
		}
		else
		{
			nb = ft_atoi(av[1]);
			sexit(nb);
		}
	}
	else
		sexit(0);
	return (0);
}
