/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:56:46 by jholland          #+#    #+#             */
/*   Updated: 2024/04/25 17:53:49 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *str, unsigned int start, unsigned int len)
{
	unsigned int	strlen;
	char			*sub;

	if (!str)
		return (NULL);
	strlen = ft_strlen(str);
	if (strlen - start < len)
		len = strlen - start;
	sub = malloc(len + 1);
	str += start;
	sub[len] = '\0';
	while (len--)
		sub[len] = str[len];
	return (sub);
}
