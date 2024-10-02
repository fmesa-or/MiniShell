/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:48:56 by jholland          #+#    #+#             */
/*   Updated: 2024/07/16 13:15:24 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_all *data, char **argv)
{
	if (!argv[1])
	{
		free(data->prog_name);
		free_varlist(&data->exported_list);
		exit(0);
	}
	else if (argv[1] && argv[2])
	{
		com_error(data, argv[0], NULL, "too many arguments");
		return (1);
	}
	else if (ft_isnumber(argv[1]))
	{
		free(data->prog_name);
		free_varlist(&data->exported_list);
		exit(ft_atoi(argv[1]));
	}
	else
	{
		com_error(data, argv[0], argv[1], "numeric argument required");
		free(data->prog_name);
		free_varlist(&data->exported_list);
		exit(2);
	}
	return (0);
}
