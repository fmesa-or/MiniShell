/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:57:06 by jholland          #+#    #+#             */
/*   Updated: 2024/04/28 15:40:09 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned int count, unsigned int size)
{
	char			*ptr;
	unsigned int	index;
	unsigned int	len;

	len = count * size;
	ptr = malloc(len);
	index = 0;
	while (index < len)
		ptr[index++] = '\0';
	return (ptr);
}
