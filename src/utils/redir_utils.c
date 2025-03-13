/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:21:09 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/12 12:49:57 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Esta funcion solo coge la siguiente palabra despues
de la redireccion, q tiene q ser el archivo al q hace ref*/
char	*getfilename(char *str, int i, t_redir *rd)
{
	int	start;

	while (ft_isspace(str[i]) && str[i])
		i++;
	start = i;
	if (!str[i] || str[i] == '<' || str[i] == '>')
		return (NULL);
	else if (str[i] == '\"')
		i = end_quote(str, i + 1, '\"');
	else if (str[i] == '\'')
		i = end_quote(str, i + 1, '\'');
	else
	{
		while (!ft_isspace(str[i]) && str[i])
			i++;
	}
	rd->end_in = i;
	return (ft_substr(str, start, i - start));
}


/*Esta ft añade al final  de la lista de redir un nuevo nodo o lo crea si esta vacia la lista*/
void	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return;
	}
	while (current && current->next)
		current = current->next;
	current->next = new;
}
