/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:46:12 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 20:30:58 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/******************************************************
*Compares two strings. If they are the same returns 0.*
******************************************************/
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
/*Esto hace join de dos str metiendo un caracter en medio de los dos
	Se puede usar como join normal pasando un nuloen el char*/
char	*ft_strcjoin(char *s1, char *s2, char c, t_data *data)
{
	int	n;
	char	*ptr;

	n = 1;
	if(c)
		n++;
	ptr = (char *)smalloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + n, data);
	if (!ptr)
		return (0);
	ptr = cjoin((char *)s1, (char *)s2, ptr, c);
	return (ptr);
}
