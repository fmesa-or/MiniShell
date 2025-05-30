/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:52:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/30 13:04:26 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_fill(t_token *tk, char *str, int rd_type, int i)
{
	t_redir	*aux_red;

	aux_red = smalloc(sizeof(t_redir));
	if (!aux_red)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes",
			NULL, NULL);
		sexit(errno);
	}
	aux_red->next = NULL;
	aux_red->index = i;
	aux_red->type = rd_type;
	if (rd_type == NDOUT || rd_type == HDOC)
		aux_red->file = getfilename(str, i + 2, aux_red, tk);
	else
		aux_red->file = getfilename(str, i + 1, aux_red, tk);
	ft_rediradd_back(&tk->redir, aux_red);
	if (!aux_red->file)
	{
		throw_error("ERROR: syntax error near unexpected token `newline'",
			NULL, NULL);
		tk->l_status = 2;
	}
	return (aux_red->end_in);
}

static char	*rd_strdel_sub(char *str, int i, int extra_len)
{
	char	*aux1;
	char	*aux2;

	aux1 = ft_substr(str, 0, i);
	aux2 = ft_substr(str, extra_len, ft_strlen(str));
	str = ft_strcjoin(aux1, aux2, ' ');
	sfree(aux1);
	sfree(aux2);
	return (str);
}

/***********************************************************************
* This removes the redirections and file names from the string of each *
* pipe, after saving it in the struct.                                 *
* Surely many lines can be shortened, probably more memory needs to be *
* freed.                                                               *
***********************************************************************/
char	*rd_strdel(t_redir *redir, char *str)
{
	int		i;
	int		extra_len;

	i = redir->index;
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			i++;
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	while (!ft_isspace(str[i]) && str[i])
		i++;
	extra_len = i;
	i = redir->index;
	if ((redir->type == HDOC || redir->type == NDOUT)
		|| (redir->type == IN || redir->type == DOUT))
	{
		str = rd_strdel_sub(str, i, extra_len);
		return (str);
	}
	return (str);
}
