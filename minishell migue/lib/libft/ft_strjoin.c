/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:54:14 by jholland          #+#    #+#             */
/*   Updated: 2024/05/07 15:06:07 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int free1, int free2)
{
	char			*join;
	unsigned int	len1;
	unsigned int	len2;
	unsigned int	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc(len1 + len2 + 1);
	i = 0;
	while (s1 && s2 && i < len1 + len2)
	{
		if (i < len1)
			join[i] = s1[i];
		if (i < len2)
			join[i + len1] = s2[i];
		i++;
	}
	join[i] = '\0';
	if (free1)
		free(s1);
	if (free2)
		free(s2);
	return (join);
}
