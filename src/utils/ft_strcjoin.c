/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:46:12 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/30 19:27:43 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cjoin(char *s1, char *s2, char *ptr, char c)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	if (c != '\0')
	{
		ptr[i] = c;
		i++;
	}
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return(ptr);
}

char	*ft_strcjoin(char const *s1, char const *s2, char c)
{
	int	n;
	char	*ptr;

	n = 1;
	if(c != '\0')
		n++;
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + n);
	if (!ptr)
		return (0);
	ptr = cjoin(s1, s2, ptr, c);
	return (ptr);
}
