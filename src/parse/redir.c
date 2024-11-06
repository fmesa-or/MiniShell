/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:52:02 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/06 19:39:04 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	tk_inrd(t_token *tk_node, char *str)
{
	int i;
	t_redir *aux_red;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '<');
		if(!str[i])
			break ;
		if (str[i] == '<' && str[i+1] == '<')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = HDOC;
			aux_red->file = getfilename(str, i + 2);
			aux_red->index = i;
			i += 2;			
		}
		else if(str[i] == '<' && str[i+1] != '<')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = IN;
			aux_red->file = getfilename(str, i + 1);
			aux_red->index = i;
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
	t_redir *aux_red;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '>');
		if(!str[i])
			break ;
		if (str[i] == '>' && str[i+1] == '>')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = NDOUT;
			aux_red->file = getfilename(str, i + 2);
			aux_red->index = i;
			i += 2;			
		}
		else if(str[i] == '>' && str[i+1] != '>')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = DOUT;
			aux_red->file = getfilename(str, i + 1);
			aux_red->index = i;
			i++;
		}
		else if (str[i] != '>' && str[i])
			i++;
	}
}
	//printredir(tk_node->redir, "out");


	/* la idea de esta funcion es usar el index del redir
	y el tipo del mismo para saber q modificacion hacer
	en cada caso*/
char	*rd_strdel(t_token *tk, char *str)
{
	int		i;
	char	*aux1;
	char	*aux2;

	i = tk->redir->index;
	if (tk->redir->type == HDOC || tk->redir->type == NDOUT)
	{
		//caso de dos
		//¿funcion q elimine chars de un str?
		aux1 = ft_substr(str, 0, i);
		aux2 = ft_substr(str, i + 2, ft_strlen(str));
		str = ft_strcjoin(aux1, aux2, ' ');
		free(aux1);
		free(aux2);
		return(str);
		
	}
	else if(tk->redir->type == IN || tk->redir->type == DOUT)
	{
		//caso de 1
		aux1 = ft_substr(str, 0, i);
		aux2 = ft_substr(str, i + 1, ft_strlen(str));
		str = ft_strcjoin(aux1, aux2, ' ');
		free(aux1);
		free(aux2);
		return(str);
	}
	else
		return(str);
}