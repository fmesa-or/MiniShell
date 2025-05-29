/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:32:22 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/29 17:22:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**********************************************************************
*Substitutes a variable expansion in a string by replacing the portion*
*between positions j-1 and i with the node's value (or empty string). *
*Returns a new allocated string with the substitution performed.      *
**********************************************************************/
char	*ft_sustit(char *str, int i, int j, t_list *node)
{
	int		size;
	char	*sub;
	char	*aux;
	char	*new_av;

	size = ft_strlen(str);
	sub = ft_substr(str, 0, j - 1);
	if (!node)
		aux = ft_strcjoin(sub, "", 0);
	else
		aux = ft_strcjoin(sub, node->value, 0);
	sfree(sub);
	sub = ft_substr(str, i, size - i);
	new_av = ft_strcjoin(aux, sub, 0);
	sfree(sub);
	sfree(aux);
	return (new_av);
}

char	*ft_expand(char *str, int i, t_list *list)
{
	int		j;
	int		n;
	char	*aux;
	t_list	*node;

	n = i + 1;
	j = n;
	while (ft_isalnum(str[n]) && str[n])
		n++;
	aux = ft_substr(str, j, n - j);
	node = find_key(list, aux);
	aux = ft_sustit(str, n, j, node);
	return (aux);
}

static int	expand_var_sub2(char *str, int i, t_data *data, t_list *list)
{
	while (str[i] != '\"' && str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			str = put_lstat(str, i, data);
		else if (str[i] == '$' && ft_isalnum(str[i + 1]))
			str = ft_expand(str, i, list);
		i++;
	}
	return (i);
}

static int	expand_var_sub(char *str, int i, t_list *list, t_token *tk)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (str[i] == '\\' && str[i + 1])
		i += 2;
	else if (str[i] == '\"')
	{
		i++;
		i = expand_var_sub2(str, i, data, list);
	}
	else if (str[i] == '\'')
		i = end_quote(str, i + 1, '\'', tk);
	else if (str[i] == '$' && str[i + 1] == '?')
		str = put_lstat(str, i, data);
	else if (str[i] == '$' && ft_isalnum(str[i + 1]))
	{
		str = ft_expand(str, i, list);
		i = -1;
	}
	return (i);
}

/**************************************************
*This function expands the variables after the $, *
*it doesn't count within single quotes or after \.*
**************************************************/
char	*expand_var(char *str, t_list *list, t_token *tk)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (i == -1)
		{
			throw_error("ERROR: expand quotes", NULL, NULL);
			return (NULL);
		}
		i = expand_var_sub(str, i, list, tk);
		i++;
	}
	return (str);
}
