/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 21:16:16 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********************************************************
*Compares 'n' bytes or stops comparing when reaching NULL*
*Returns -1, 0 or 1.                                     *
*********************************************************/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && n != 0)
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		else if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

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
			str[i] = str[i] + 32;
	}
	return (str);
}

/*******************************************************
*Reserves memory (with smalloc) and returns a new string*
*formed by the concatenation of 's1' and 's2'          *
*******************************************************/
char	*ft_strjoin(char const *s1, char const *s2, t_data *data)
{
	char	*str;
	size_t	sizestr;
	size_t	i;
	size_t	j;

	sizestr = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = smalloc(sizestr, data);
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

/**************************
*Special GNL for MINISHELL*
**************************/
/*
int	ms_gnl(char **line)
{
	int		i;
	int		r;
	char	c;
	char	*buffer;

	i = 0;
	r = 0;
	buffer = (char *)smalloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && (c != '\n' && c != '\0'))
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	sfree(buffer, data);
	return (r);
}
*/