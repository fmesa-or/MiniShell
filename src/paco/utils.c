/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/01 15:31:27 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************
*Converts every string to lowercase*
***********************************/
char	*ms_tolower_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] == str[i] + 32;
	}
	return (str);
}

/**********************************************************************
*Allocates enough memory to copy 's1'. Copies and returns the pointer.*
*If there is no enough space available for memory, returns NULL       *
**********************************************************************/
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	char	*s1_;
	int		i;

	s1_ = (char *)s1;
	i = 0;
	while (s1_[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1_[i])
	{
		ptr[i] = s1_[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*******************************************************
*Reserves memory (with malloc) and returns a new string*
*formed by the concatenation of 's1' and 's2'          *
*******************************************************/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	sizestr;
	size_t	i;
	size_t	j;

	sizestr = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizestr);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = (char )s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = (char )s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}


/****************************************************************************
*Looks for a string inside a bigger string. Only looks for 'len' characters.*
*Every char after '\0' it's not checked.                                    *
****************************************************************************/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ndle;
	char	*hystck;
	size_t	i;
	size_t	j;

	ndle = (char *)needle;
	hystck = (char *)haystack;
	i = 0;
	if (ndle[0] == '\0')
		return (hystck);
	while (hystck[i] && i < len)
	{
		j = 0;
		while (hystck[i + j] == ndle[j] && i + j < len)
		{
			if (ndle[j + 1] == '\0' && j + 1 <= len)
				return (&hystck[i]);
			j++;
		}
		i++;
	}
	return (0);
}