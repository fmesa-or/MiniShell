/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:52:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/12/05 16:06:00 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_fill(t_token *tk, char *str, int rd_type, int i)
{
	t_redir *aux_red;
	
	aux_red = malloc(sizeof(t_redir));
	ft_rediradd_back(&tk->redir, aux_red);
	aux_red->index = i;
	aux_red->type = rd_type;
	if (rd_type == NDOUT || rd_type == HDOC)
		aux_red->file = getfilename(str, i + 2);
	else if (rd_type == DOUT)
		aux_red->file = getfilename(str, i + 1);
	else if (rd_type == IN)
	{
		aux_red->file = getfilename(str, i + 1);
		if (!aux_red->file)
			throw_error("ERROR: wrong or not existing file", tk, NULL);
	}
}

void	tk_inrd(t_token *tk_node, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '<');
		if(!str[i])
			break ;
		if (str[i] == '<' && str[i+1] == '<')
		{
			redir_fill(tk_node, str, HDOC, i);
			i += 2;			
		}
		else if(str[i] == '<' && str[i+1] != '<')
		{
			redir_fill(tk_node, str, IN, i);
			i++;
		}
		else if (str[i] != '<' && str[i])
			i++;
	}
}
	//printredir(tk_node->redir, "in");
	
void	tk_outrd(t_token *tk_node, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '>');
		if(!str[i])
			break ;
		if (str[i] == '>' && str[i+1] == '>')
		{
			redir_fill(tk_node, str, NDOUT, i);
			i += 2;			
		}
		else if(str[i] == '>' && str[i+1] != '>')
		{
			redir_fill(tk_node, str, DOUT, i);
			i++;
		}
		else if (str[i] != '>' && str[i])
			i++;
	}
}
	//printredir(tk_node->redir, "out");


	/* Esto elimina las redir y el file name del str
		de cada pipe, despues de guardarlo en la struc.
		Seguro q se pueden abrebiar muchas lineas, 
		segurqmente hay q liberar mas memoria*/
char	*rd_strdel(t_token *tk, char *str)
{
	int		i;
	int		extra_len;
	char	*aux1;
	char	*aux2;

	i = tk->redir->index;
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i+1] == '<' || str[i+1] == '>')
			i++;
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	while (!ft_isspace(str[i]))
		i++;
	extra_len = i;
	i = tk->redir->index;
	if (tk->redir->type == HDOC || tk->redir->type == NDOUT)
	{
		//caso de dos
		aux1 = ft_substr(str, 0, i);
		aux2 = ft_substr(str, extra_len, ft_strlen(str));
		str = ft_strcjoin(aux1, aux2, ' ');
		free(aux1);
		free(aux2);
		return(str);
		
	}
	else if (tk->redir->type == IN || tk->redir->type == DOUT)
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
