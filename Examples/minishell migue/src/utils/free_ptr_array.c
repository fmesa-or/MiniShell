/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ptr_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:04:16 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 14:05:39 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_ptr_array(char	***array)
{
	char	**tmp;

	if (!*array)
		return ;
	tmp = *array;
	while (*tmp)
	{
		free(*tmp);
		*(tmp++) = NULL;
	}
	free(*array);
	*array = NULL;
}
