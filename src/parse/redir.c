/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:52:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 23:52:44 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_fill(t_token *tk, char *str, int rd_type, int i, t_data *data)
{
	t_redir *aux_red;

	aux_red = smalloc(sizeof(t_redir), data);
	if (!aux_red)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		sexit(errno, data);
	}
	aux_red->next = NULL;
	aux_red->index = i;
	aux_red->type = rd_type;
	if (rd_type == NDOUT || rd_type == HDOC)
		aux_red->file = getfilename(str, i + 2, aux_red, tk, data);
	else
		aux_red->file = getfilename(str, i + 1, aux_red, tk, data);
	ft_rediradd_back(&tk->redir, aux_red);
//	printf("\nred indx = %i,  archivo = %s\n", aux_red->index, aux_red->file);
/* 	while (tk->redir->next)
	{
		printf("\n redirfill: \n");
		tk->redir = tk->redir->next;
	} */
	return(aux_red->end_in);
}

//printredir(tk_node->redir, "out");


/* Esto elimina las redir y el file name del str
de cada pipe, despues de guardarlo en la struc.
Seguro q se pueden abrebiar muchas lineas, 
segurqmente hay q liberar mas memoria*/
char	*rd_strdel(t_redir *redir, char *str, t_data *data)
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
		aux1 = ft_substr(str, 0, i, data);
		aux2 = ft_substr(str, extra_len, ft_strlen(str), data);
		str = ft_strcjoin(aux1, aux2, ' ', data);
		sfree(aux1, data);
		sfree(aux2, data);
		return(str);
		
	}
	else if (redir->type == IN || redir->type == DOUT)
	{
		//caso de 1
		aux1 = ft_substr(str, 0, i, data);
		aux2 = ft_substr(str, extra_len, ft_strlen(str), data);
		str = ft_strcjoin(aux1, aux2, ' ', data);
		sfree(aux1, data);
		sfree(aux2, data);
		return(str);
	}
	else
		return(str); 
}

/* void	tk_inrd(t_token *tk_node, char *str)
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
} */