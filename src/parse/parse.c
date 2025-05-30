/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:13:43 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/30 12:26:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************************************************
* This function iterates through the string until it finds a valid     *
* pipe. Then returns the int of its position, which is useful to       *
* resume from that value.                                              *
***********************************************************************/
int	pipe_iteri(char *str, int i, char c)
{
	while (str[i] != c && str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i += 2;
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		i++;
	}
	return (i);
}

/***********************************************************************
* This function counts the segments between |, without considering     *
* those that are within quotes and such.                               *
* IMPORTANT: if there's a pipe as first or last char it counts them,   *
* both cases must have different treatments:                           *
*	If str[0] = |, it should give an error as the first pipe is empty. *
*	If the last str[i] = |, it should let the last chunk be written    *
*	through terminal.                                                  *
***********************************************************************/
int	pipe_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		i = pipe_iteri(str, i, '|');
		if (str[i] == '|')
		{
			if (!str[i + 1])
				count++;
			i++;
		}
	}
	return (count);
}

char	**check_pipes(char **pipes, t_data *data)
{
	int	i;

	i = 0;
	if (!pipes)
	{
		throw_error("ERROR: no pipes", NULL, data);
		return (NULL);
	}
	while (pipes[i])
	{
		if (!pipes[i][0] || str_isspace(pipes[i]) == 0)
		{
			pipes[i] = readline("> ");
		}
		i++;
	}
	return (pipes);
}

t_token	*parse_main(char *str, t_list *list, t_data *data)
{
	char	**av;
	char	*aux;
	t_token	*tokens;

	av = NULL;
	tokens = NULL;
	if (str[0] == '|')
	{
		throw_error("Minishell: syntax error near unexpected token",
			NULL, NULL);
		data->l_status = 2;
		return (NULL);
	}
	aux = expand_var(str, list, NULL);
	av = check_pipes(pipe_separator(aux, data), data);
	if (!av)
		return (NULL);
	tokens = tk_list_make(av, list, data);
	free_2ptr(av);
	if (!tokens)
		return (NULL);
	return (tokens);
}
