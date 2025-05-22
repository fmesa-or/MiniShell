/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:03:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 23:29:20 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**********************************************************************
*Allocates enough memory to copy 's1'. Copies and returns the pointer.*
*If there is no enough space available for memory, returns NULL       *
**********************************************************************/
char	*ft_strdup(const char *s1, t_data *data)
{
	char		*ptr;
	int		i;

	ptr = (char *) smalloc(sizeof(char) * (ft_strlen(s1) + 1), data);
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

char	*ft_substr(char const *s, unsigned int start, size_t len, t_data *data)
{
	size_t			size;
	char			*ptr;
	size_t			j;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup("", data));
	else if (size - start < len)
		len = size - start;
	ptr = smalloc(sizeof(char) * (len + 1), data);
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

static char	**new_clear(char ***ptr, t_data *data)
{
	int	i;

	if (ptr && *ptr)
	{
		i = 0;
		while ((*ptr)[i])
		{
			sfree((*ptr)[i], data);
			(*ptr)[i] = NULL;
			i++;
		}
		sfree(*ptr, data);
		*ptr = NULL;
	}
	return (*ptr);
}

char	**fill_split(char **ptr, char const *s, char c, t_data *data)
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
				ptr[k] = ft_substr(s, i, j, data);
				if (!ptr[k++])
					return (new_clear(&ptr, data));
				i += j;
			}
		}
		else
			i++;
	}
	ptr[k] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c, t_data *data)
{
	int		words;
	char	**ptr;

	if (!s)
		return (NULL);
	words = ft_countstr(s, c);
	ptr = smalloc(sizeof(char *) * (words + 1), data);
	if (!ptr)
		return (NULL);
	ptr = fill_split(ptr, s, c, data);
	return (ptr);
}

t_list	*ft_lstnew(char *n_key, char *n_value, t_data *data)
{
	t_list *node;

	node = smalloc(sizeof(t_list), data);
	if (!node)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		sexit(errno, data);
	}
	node->key = n_key;
	node->value = n_value;
	node->next = NULL;
	return (node);
}