/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:21:09 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/29 19:04:16 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************************
*Returns the last node of redir list*
************************************/
t_redir	*ft_redirlast(t_redir *rd)
{
	t_redir	*node;

	node = rd;
	while (node)
	{
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (node);
}

int	get_redir(t_token *tk, char *str, int j)
{
	int	rd_end;

	rd_end = 0;
	if (str[j] == '<' && str[j + 1] == '<')
		rd_end = redir_fill(tk, str, HDOC, j);
	else if (str[j] == '>' && str[j + 1] == '>')
		rd_end = redir_fill(tk, str, NDOUT, j);
	else if (str[j] == '<')
		rd_end = redir_fill(tk, str, IN, j);
	else if (str[j] == '>')
		rd_end = redir_fill(tk, str, DOUT, j);
	return (rd_end);
}

static int	getfilename_sub(char *str, t_redir *rd, int i)
{
	while (!ft_isspace(str[i]) && str[i])
		i++;
	rd->end_in = i;
	return (i);
}

/***********************************************************************
* This function only takes the next word after the redirection, which  *
* has to be the file it refers to.                                     *
***********************************************************************/
char	*getfilename(char *str, int i, t_redir *rd, t_token *tk)
{
	int		start;
	char	*aux;
	t_data	*data;

	aux = NULL;
	data = get_pdata(NULL);
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
		i = getfilename_sub(str, rd, i);
		return (ft_substr(str, start, i - start));
	}
}

/***********************************************************************
* This function adds a new node at the end of the redirection list or  *
* creates it if the list is empty.                                     *
***********************************************************************/
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
