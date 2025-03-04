/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:21:09 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/04 11:16:18 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion solo coge la siguiente palabra despues
de la redireccion, q tiene q ser el archivo al q hace ref*/

char	*getfilename(char *str, int i)
{
	int	start;

	while (ft_isspace(str[i]) && str[i])
		i++;
	start = i;
	if (!str[i] || str[i] == '<' || str[i] == '>')
		return (NULL);
	else if (str[i] == '\"')
	{
		i = end_quote(str, i + 1, '\"');
		return (ft_substr(str, start, i - start));
	}
	else if (str[i] == '\'')
	{
		i = end_quote(str, i + 1, '\'');
		return (ft_substr(str, start, i - start));
	}
	else
	{
		while (!ft_isspace(str[i]) && str[i])
			i++;
		return (ft_substr(str, start, i - start));
	}
}

void	ft_rediradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		while (*lst)
		{
			if ((*lst)->next)
				(*lst) = (*lst)->next;
			else
				break ;
		}
		temp = (*lst);
		temp->next = new;
	}
}
