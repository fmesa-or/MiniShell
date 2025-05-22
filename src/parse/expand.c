/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:32:22 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 20:53:15 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*la i esta en el ultimo char de lo q se va a expan
la j esta en el siguiente char al $*/
char	*ft_sustit(char *str, int i, int j, t_list *node, t_data *data)
{
	int		size;
	char	*sub;
	char	*aux;
	char	*new_av;

	size = ft_strlen(str);
	sub = ft_substr(str, 0, j - 1, data);
	if (!node)
		aux = ft_strcjoin(sub, "", 0, data);
	else
		aux = ft_strcjoin(sub, node->value, 0, data);
	sfree(sub, data);
	sub = ft_substr(str, i, size - i, data);
	new_av = ft_strcjoin(aux, sub, 0, data);
	sfree(sub, data);
	sfree(aux, data);
	return (new_av);	
}

char	*ft_expand(char *str, int *i, t_list *list, t_data *data)
{
	int	j;
	int	n;
	char	*aux;
	t_list	*node;

	n = (*i) + 1;
	j = n;
	while(ft_isalnum(str[n]) && str[n])
		n++;
	aux =ft_substr(str, j, n - j, data);
	node = find_key(list, aux);
	aux = ft_sustit(str, n, j, node, data);
	(*i) += ft_strlen(list->value) - ft_strlen(list->key); 
	return (aux);
}

/*comprobar que las mates estan bien hechas, pero en principio tendria q impimir bien*/
char	*put_lstat(char  *str, int *i, t_data *data)
{
	int		n;
	char	*stat;
	char	*aux;
	char	*sub;

	n = (*i);
	stat = ft_itoa(data->l_status, data);
	sub = ft_substr(str, 0, n, data);
	aux = ft_strcjoin(sub, stat, ' ', data);
	sfree(sub, data);
	sfree(stat, data);
	sub = ft_substr(str, n + 2, ft_strlen(str), data);
	stat = ft_strcjoin(aux, sub, ' ', data);
	sfree(aux, data);
	sfree(sub, data);
	return (stat);
}

/*Esta funcion expande las variables despues del $,
no cuenta entre comillas simples ni despues de \.*/
char	*expand_var(char *str, t_list *list, t_data *data, t_token *tk)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (i == -1)
		{
			throw_error("ERROR: expand quotes", NULL, NULL);
			return(NULL);
		}
		if (str[i] == '\\' && str[i+1])
			i += 2;
		else if (str[i] == '\"')// si expande
		{
			i++;
			while (str[i] != '\"' && str[i])
			{
				if (str[i] == '$' && str[i + 1] == '?')
					str = put_lstat(str, &i, data);
				else if (str[i] == '$' && ft_isalnum(str[i+1]))
					str = ft_expand(str, &i, list, data);
				i++;
			}
		}
 		else if (str[i] == '\'') // Q NO EXPAMNDA
			i = end_quote(str, i + 1, '\'', tk);
		else if (str[i] == '$' && str[i + 1] == '?')
			str = put_lstat(str, &i, data);
		else if (str[i] == '$' && ft_isalnum(str[i+1]))
			str = ft_expand(str, &i, list, data);
		i++;
	}
	return (str);
}
