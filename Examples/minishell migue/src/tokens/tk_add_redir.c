/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_add_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:19:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 19:44:22 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redir_type(t_redir *node, char *line)
{
	if (line[0] == '>' && line[1] != '>')
		node->type = GT;
	else if (line[0] == '<' && line[1] != '<')
		node->type = LT;
	else if (line[0] == '>' && line[1] == '>')
		node->type = GGT;
	else if (line[0] == '<' && line[1] == '<')
		node->type = LLT;
}

void	tk_add_redir(t_token *node, char **line, t_all *data)
{
	t_redir			*redir_node;
	t_redir			*new_node;
	char			*arg;

	new_node = malloc(sizeof(t_redir));
	set_redir_type(new_node, *line);
	*line += 1;
	if (new_node->type == LLT || new_node->type == GGT)
		*line += 1;
	arg = get_arg(data, line);
	new_node->file = parse_arg(data, arg);
	free(arg);
	new_node->next = NULL;
	if (!node->redir)
		node->redir = new_node;
	else
	{
		redir_node = node->redir;
		while (redir_node && redir_node->next)
			redir_node = redir_node->next;
		redir_node->next = new_node;
	}
}
