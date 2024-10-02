/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:27:16 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 19:56:23 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	search_arg_end(char *line)
{
	unsigned int	end;
	int				esc;
	char			quoted;

	end = 0;
	esc = 0;
	quoted = '\0';
	while (esc || quoted || (line[end] && line[end] != '|'
			&& line[end] != '<' && line[end] != '>' && !ft_isspace(line[end])))
	{
		if (!esc && !quoted && line[end] == '\\')
			esc = 1;
		else if (!esc && !quoted && (line[end] == '\'' || line[end] == '\"'))
			quoted = line[end];
		else if (!esc && quoted == line[end])
			quoted = '\0';
		else
			esc = 0;
		end++;
	}
	return (end);
}

char	*subst_tilde(t_all *data, char *line)
{
	char			*out;

	if (line[0] == '~' && (line[1] == '\0' || line [1] == '/'))
	{
		out = ft_strjoin(data->home, &line[1], 0, 0);
		free(line);
		return (out);
	}
	else
		return (line);
}

char	*get_arg(t_all *data, char **line)
{
	unsigned int	len;
	char			*arg;

	arg = NULL;
	while (**line && ft_isspace(**line))
		*line += 1;
	if (!**line || **line == '|' || **line == '<' || **line == '>')
		return (NULL);
	len = search_arg_end(*line);
	if (len)
		arg = ft_substr(*line, 0, len);
	*line += len;
	while (**line && ft_isspace(**line))
		*line += 1;
	arg = subst_tilde(data, arg);
	return (arg);
}
