/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:51:16 by jholland          #+#    #+#             */
/*   Updated: 2024/07/16 13:14:50 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	com_error(t_all *data, char *com, char *arg, char *message)
{
	if (data)
	{
		write(2, data->prog_name, ft_strlen(data->prog_name));
		write(2, ": ", 2);
	}
	if (com)
	{
		write(2, com, ft_strlen(com));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	return (1);
}

int	com_not_found(t_all *data, char **argv)
{
	return (com_error(data, argv[0], NULL, "command not found"));
}
