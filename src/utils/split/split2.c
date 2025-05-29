/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:57:49 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 18:58:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			size;
	char			*ptr;
	size_t			j;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	else if (size - start < len)
		len = size - start;
	ptr = smalloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < len && s[start + j])
	{
		ptr[j] = s[start + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**ptr;

	if (!s)
		return (NULL);
	words = ft_countstr(s, c);
	ptr = smalloc(sizeof(char *) * (words + 1));
	if (!ptr)
		return (NULL);
	ptr = fill_split(ptr, s, c);
	return (ptr);
}
