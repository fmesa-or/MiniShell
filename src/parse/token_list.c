/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/14 18:50:56 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tk_init(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->command = NULL;
	new->redir = NULL;
	new->next = NULL;
	new->argv = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
	return (new);
}

t_token	*tk_list_init(char **pipes)
{
	int	i;

	i = 0;
	t_token	*tk_list;
	tk_list = tk_init();
	while (pipes[i])
	{
		tk_list->next = tk_init();
		tk_list = tk_list->next;
		i++;
	}
	return(tk_list);
}


