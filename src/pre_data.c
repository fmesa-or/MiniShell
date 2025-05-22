/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:16:51 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 22:45:33 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;
	char	*a;

	i = 0;
	a = (char *)str;
	while (i < len)
	{
		a[i] = c;
		i++;
	}
	return (a);
}

t_data	*pre_data_init(void)
{
	t_data	*pre_data_init;

	pre_data_init = malloc(sizeof(t_data));
	if (!pre_data_init)
	{
		throw_error("ERROR: predata malloc dramatic failure", NULL, NULL);	
		exit(errno);
	}
	ft_memset(pre_data_init->fd_table, 0, sizeof(pre_data_init->fd_table));
	ft_memset(pre_data_init->mem_table, 0, sizeof(pre_data_init->mem_table));
	return (pre_data_init);
}