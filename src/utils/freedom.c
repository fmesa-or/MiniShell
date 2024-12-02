/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:13:54 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/28 19:37:42 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2ptr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_partial_data(t_data *data)
{
	if (data->cmnds)
	{
		free_2ptr(data->cmnds);
		data->cmnds = NULL;
	}
	if (data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
}

void	free_all_data(t_data *data)
{
	free_partial_data(data);
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->home)
	{
		free(data->home);
		data->home = NULL;
	}
	//freelist(data.list)
}
