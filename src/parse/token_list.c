/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/06 19:29:46 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tk_init(t_token *new)
{
	new->type = PIPE;
	new->command = NULL;
	new->redir = NULL;
	new->argv = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
}


t_token	*tk_list_make(char **pipes)
{
	int	i;
	char *aux;
	t_token	*tk_list;

	i = 0;
	while (pipes[i])
		i++;
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i  = 0;	
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		tk_inrd(&tk_list[i], pipes[i]);
		tk_outrd(&tk_list[i], pipes[i]);
		if (tk_list[i].redir->type){
			aux = rd_strdel(&tk_list[i], pipes[i]);
			printf("str = %s\n", aux);
			}
		i++;
	}
	tk_list[i].type = NONE;
	return(tk_list);
}


