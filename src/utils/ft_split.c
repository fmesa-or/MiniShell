/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:27:13 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/02 20:16:21 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if ((int)(start + len) > (int)ft_strlen(s))
		len = ft_strlen(s) - start;
	if ((int)start >= (int)ft_strlen(s))
		len = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	cont_word(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if ((s[i + 1] == '\0' || s[i + 1] == c) && s[i] != c)
			j++;
		i++;
	}
	return (j);
}

int	ft_free(const char *sub_s, char **ptr, char c, int *k)
{
	int	j;

	j = 0;
	while (sub_s[j] != c && sub_s[j])
		j++;
	ptr[*k] = ft_substr(sub_s, 0, j);
	if (!ptr[*k])
	{
		while (*k >= 0)
			free(ptr[(*k)--]);
		free(ptr);
		return (-1);
	}
	(*k)++;
	return (*k);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = -1;
	k = 0;
	ptr = malloc (sizeof(char *) * (cont_word(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[++i])
	{
		j = 0;
		if (s[i] != c)
		{
			while (s[i + j] != c && s[i + j])
				j++;
			k = ft_free(&s[i], ptr, c, &k);
			if (k == -1)
				return (NULL);
			i += j -1;
		}
	}
	ptr[k] = 0;
	return (ptr);
}
