/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:32:22 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/12 17:18:52 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*la i esta en el ultimo char de lo q se va a expan
la j esta en el siguiente char al $*/
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
	free(sub);
	sub = ft_substr(str, i, size - i);
	new_av = ft_strcjoin(aux, sub, 0);
	free(sub);
	free(aux);
	return (new_av);	
}

char	*ft_expand(char  *str, int *i, t_list *list)
{
	int	j;
	int	n;
	char	*aux;
	t_list	*node;

	n = (*i) + 1;
	j = n;
	while(ft_isalnum(str[n]) && str[n])
		n++;
	aux =ft_substr(str, j, n - j);
	node = find_key(list, aux);
	aux = ft_sustit(str, n, j, node);
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
	stat = ft_itoa(data->l_status);
	sub = ft_substr(str, 0, n);
	aux = ft_strcjoin(sub, stat, ' ');
	free(sub);
	free(stat);
	sub = ft_substr(str, n + 2, ft_strlen(str));
	stat = ft_strcjoin(aux, sub, ' ');
	free(aux);
	free(sub);
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
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == '\'')// Q NO EXPAMNDA	
		{
			i = end_quote(str, i + 1, '\'', tk);
			
		}
		else if (str[i] == '$' && str[i + 1] == '?')
			str = put_lstat(str, &i, data);
		else if (str[i] == '$' && ft_isalnum(str[i+1]))
			str = ft_expand(str, &i, list);
		i++;
	}
	return(str);
}
