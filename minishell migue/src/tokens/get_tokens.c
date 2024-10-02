/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:23 by jholland          #+#    #+#             */
/*   Updated: 2024/07/16 12:57:15 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->pid = 0;
	new->command = NULL;
	new->redir = NULL;
	new->next = NULL;
	new->argc = 0;
	new->argv = NULL;
	new->fd[0] = 0;
	new->fd[1] = 1;
	return (new);
}

static void	add_to_list(t_token **tk_list, t_token *new)
{
	t_token			*tmp;

	if (!*tk_list)
	{
		*tk_list = new;
		new->prev = NULL;
	}
	else
	{
		tmp = *tk_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

static void	add_token(t_token **tk_list, char **line, t_all *data)
{
	t_token			*new;

	if (**line == '\0')
		return ;
	new = new_token();
	if (**line == '|')
	{
		new->type = PIPE;
		*line += 1;
	}
	else
	{
		new->type = CMD;
		tk_set_command(new, line, data);
	}
	add_to_list(tk_list, new);
}

void	get_tokens(t_token **tk_list, char *line, t_all *data)
{
	while (line && *line)
	{
		while (*line && ft_isspace(*line))
			line++;
		add_token(tk_list, &line, data);
	}
}
