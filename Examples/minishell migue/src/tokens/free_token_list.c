/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:14:46 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:25 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **tk_list)
{
	t_token	*next_tk;
	t_redir	*next_rd;

	if (!*tk_list)
		return ;
	while (*tk_list)
	{
		next_tk = (*tk_list)->next;
		while ((*tk_list)->redir)
		{
			next_rd = (*tk_list)->redir->next;
			free((*tk_list)->redir->file);
			free((*tk_list)->redir);
			(*tk_list)->redir = next_rd;
		}
		free((*tk_list)->command);
		free_ptr_array(&(*tk_list)->argv);
		free(*tk_list);
		*tk_list = next_tk;
	}
	*tk_list = NULL;
}
