/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/26 17:35:46 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tk_init(t_token *new)
{
	new->type = PIPE;
	new->command = NULL;
	new->redir = NULL;
	new->argv = NULL;
	new->av_list = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
}

t_token	*tk_list_make(char **pipes, t_list *env, t_data *data)
{
	int		i;
	int		j;
	t_token	*tk_list;
	
	i = 0;
	j = 0;
	while (pipes[i])
		i++;
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i = 0;
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		j = 0;
		while(pipes[i][j]) //en este buble inspeccionamos la linea de cada pipe char x char
		{
			while (ft_isspace(pipes[i][j]))
				j++;				
			if (pipes[i][j] == '<' || pipes[i][j] == '>')
			{
				get_redir(&tk_list[i], pipes[i], j, data);
				pipes[i] = rd_strdel(ft_redirlast(tk_list[i].redir), pipes[i]); //añadir lo de las comillas
			}
			else if (pipes[i][j] && (pipes[i][j] != '<' && pipes[i][j] != '>' && !ft_isspace(pipes[i][j])))
				j = get_av(&tk_list[i].av_list, pipes[i], j);//funcion q saca un arg, teniendo en cuenta q este primer char puede ser ' o ";
		}
		tk_list[i].argv = listtoargv(tk_list[i].av_list);
		tk_argvtipe(&tk_list[i], env, data);
		i++;
	}
	tk_list[i].type = NONE;
	return (tk_list);
}
