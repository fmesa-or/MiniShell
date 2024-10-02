/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_set_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:20:21 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 19:44:27 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_redir(char **line)
{
	if (((*line)[0] == '<' && (*line)[1] == '<')
		|| ((*line)[0] == '>' && (*line)[1] == '>'))
		*line += 2;
	else if (**line == '<' || **line == '>')
		*line += 1;
	else
		return ;
	while (ft_isspace(**line))
		*line += 1;
	if (!**line || **line == '<' || **line == '>' || **line == '|')
		return ;
	*line += search_arg_end(*line);
	while (ft_isspace(**line))
		*line += 1;
}

static unsigned int	count_args(char *line)
{
	unsigned int	end;
	unsigned int	count;

	count = 0;
	while (*line && *line != '|')
	{
		while (*line && ft_isspace(*line))
			line++;
		if (*line == '<' || *line == '>')
			skip_redir(&line);
		else if (*line && *line != '|')
		{
			end = search_arg_end(line);
			count++;
			line += end;
		}
	}
	return (count);
}

void	tk_set_command(t_token *node, char **line, t_all *data)
{
	unsigned int	arg_i;
	char			*arg;

	node->argc = count_args(*line);
	node->argv = malloc(sizeof(char *) * (node->argc + 1));
	arg_i = 0;
	while (**line && **line != '|')
	{
		if (**line == '<' || **line == '>')
			tk_add_redir(node, line, data);
		else if (**line != '|')
		{
			arg = get_arg(data, line);
			node->argv[arg_i++] = parse_arg(data, arg);
			free(arg);
		}
	}
	node->argv[arg_i] = NULL;
	if (is_builtin(node->argv))
		node->type = BUIL;
}
