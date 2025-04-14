/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:52:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/26 17:29:17 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_redir(t_token *tk, char *str, int j, t_data *data)
{
	int	rd_end;
	
	rd_end = 0;
	if (str[j] == '<' && str[j + 1] == '<')
		rd_end = redir_fill(tk, str, HDOC, j, data);
	else if (str[j] == '>' && str[j + 1] == '>')
		rd_end = redir_fill(tk, str, NDOUT, j, data);
	else if (str[j] == '<')
		rd_end = redir_fill(tk, str, IN, j, data);
	else if (str[j] == '>')
		rd_end = redir_fill(tk, str, DOUT, j, data);
	return(rd_end);
}

int	redir_fill(t_token *tk, char *str, int rd_type, int i, t_data *data)
{
	t_redir *aux_red;

	aux_red = malloc(sizeof(t_redir));
	aux_red->next = NULL;
	aux_red->index = i;
	aux_red->type = rd_type;
	if (rd_type == NDOUT || rd_type == HDOC)
		aux_red->file = getfilename(str, i + 2, aux_red, tk, data);
	else
		aux_red->file = getfilename(str, i + 1, aux_red, tk, data);
	ft_rediradd_back(&tk->redir, aux_red);
	return(aux_red->end_in);
}


/* Esto elimina las redir y el file name del str
de cada pipe, despues de guardarlo en la struc.
Seguro q se pueden abrebiar muchas lineas, 
segurqmente hay q liberar mas memoria*/
char	*rd_strdel(t_redir *redir, char *str)
{
	int		i;
	int		extra_len;
	char	*aux1;
	char	*aux2;
	
	i = redir->index;
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i+1] == '<' || str[i+1] == '>')
		i++;
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	while (!ft_isspace(str[i]) && str[i]) //revisar comillas
		i++;
	extra_len = i;
	i = redir->index;
	if (redir->type == HDOC || redir->type == NDOUT)
	{
		//caso de dos
		aux1 = ft_substr(str, 0, i);
		aux2 = ft_substr(str, extra_len, ft_strlen(str));
		str = ft_strcjoin(aux1, aux2, ' ');
		free(aux1);
		free(aux2);
		return(str);
		
	}
	else if (redir->type == IN || redir->type == DOUT)
	{
		//caso de 1
		aux1 = ft_substr(str, 0, i);
		aux2 = ft_substr(str, extra_len, ft_strlen(str));
		str = ft_strcjoin(aux1, aux2, ' ');
		free(aux1);
		free(aux2);
		return(str);
	}
	else
		return(str); 
}
