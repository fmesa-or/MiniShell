/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:21:09 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/12 14:29:49 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Esta funcion solo coge la siguiente palabra despues
de la redireccion, q tiene q ser el archivo al q hace ref*/
char	*getfilename(char *str, int i, t_redir *rd, t_token *tk, t_data *data)
{
	int		start;
	char	*aux;

	aux = NULL;
	while (ft_isspace(str[i]) && str[i])
		i++;
	start = i;
	if (!str[i] || str[i] == '<' || str[i] == '>')
		return (NULL);
	else if (str[i] == '\'' || str[i] == '\"')
	{
		i = end_quote(str, i + 1, str[i], tk);
		rd->end_in = i;
		aux = ft_substr(str, start + 1, i - start - 1);
		if (ft_strlen(aux) == 0)
			throw_error("NO file name", tk, data);
		return (aux);
	}
	else
	{
		while (!ft_isspace(str[i]) && str[i])
			i++;
		rd->end_in = i;
		return (ft_substr(str, start, i - start));
	}
}


/*Esta ft añade al final  de la lista de redir un nuevo nodo o lo crea si esta vacia la lista*/
void	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current && current->next)
		current = current->next;
	current->next = new;
}