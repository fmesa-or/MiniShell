/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:18:59 by jholland          #+#    #+#             */
/*   Updated: 2024/07/11 14:03:57 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	split_count(char *str, char sep)
{
	unsigned int	count;

	count = 0;
	while (str && *str)
	{
		if (*str == sep)
			while (*str == sep)
				str++;
		else
		{
			count++;
			while (*str && *str != sep)
				str++;
		}
	}
	return (count);
}

char	**ft_split(char	*str, char sep)
{
	char			**split;
	unsigned int	i;
	unsigned int	len;

	split = malloc(sizeof(char *) * (split_count(str, sep) + 1));
	i = 0;
	while (str && *str)
	{
		if (*str == sep)
			while (*str == sep)
				str++;
		else
		{
			len = 0;
			while (str[len] && str[len] != sep)
				len++;
			split[i++] = ft_substr(str, 0, len);
			str += len;
		}
	}
	split[i] = NULL;
	return (split);
}
