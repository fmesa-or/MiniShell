/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:32:22 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/21 18:38:50 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*la i esta en el ultimo char de lo q se va a expan
la j esta en el siguiente char al $*/
char	*ft_sustit(char *str, int i, int j, t_list *node)
{
	int	size;
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
/*Esta funcion expande las variables despues del $,
no cuenta entre comillas simples ni despues de \.*/

char	*expand_var(char *str, t_list *list)
{
	int i;
	char *aux;

	i = 0;
	aux = str;
	while(str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == '\'')
		{	
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			//funcion q elimine sustitua el $? por el l_status del struc data			
		}
		else if (str[i] == '$' && ft_isalnum(str[i+1])) //esto realmente mirar dentro del if, por q si falla el char hay q dar error
		{
			aux = ft_expand(str, &i, list);
			//free(str);
			str = aux;
		}
		i++;
	}
	return(aux);
}
