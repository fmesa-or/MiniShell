/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:00:42 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 22:29:53 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freearray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	while (--i >= 0)
		sfree(array[i]);
	if (array)
		sfree(array);
}
