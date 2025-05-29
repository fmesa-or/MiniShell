/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:14:29 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/29 19:08:11 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**********************************************************************
*Allocates enough memory to copy 's1'. Copies and returns the pointer.*
*If there is no enough space available for memory, returns NULL       *
**********************************************************************/
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	ptr = (char *) smalloc(sizeof(char) * (ft_strlen(s1)+1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_countstr(char const *s, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (size);
}

char	**ft_clear(char ***ptr)
{
	int	i;

	if (ptr && *ptr)
	{
		i = 0;
		while ((*ptr)[i])
		{
			sfree((*ptr)[i]);
			(*ptr)[i] = NULL;
			i++;
		}
		sfree(*ptr);
		*ptr = NULL;
	}
	return (*ptr);
}

static int	fill_split2(const char *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (j);
}

char	**fill_split(char **ptr, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = fill_split2(s, i, c);
			if (j)
			{
				ptr[k] = ft_substr(s, i, j);
				if (!ptr[k++])
					return (ft_clear(&ptr));
				i += j;
			}
		}
		else
			i++;
	}
	ptr[k] = 0;
	return (ptr);
}
