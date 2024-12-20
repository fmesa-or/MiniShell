/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:46:12 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/14 18:56:01 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


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
	if (c)
	{
		ptr[i] = c;
		i++;
	}
	while (s2 && s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return(ptr);
}

char	*ft_strcjoin(char *s1, char *s2, char c)
{
	int	n;
	char	*ptr;

	n = 1;
	if(c)
		n++;
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + n);
	if (!ptr)
		return (0);
	ptr = cjoin(s1, s2, ptr, c);
	return (ptr);
}
