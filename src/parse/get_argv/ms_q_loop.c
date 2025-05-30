/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:41:10 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/30 12:18:37 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_quote_loop_sub(char *str, int *j, char *av)
{
	int		start;
	char	*nav;

	start = (*j);
	while (str[(*j)] && str[(*j)] != ' ')
	{
		if (str[(*j)] == '\'' || str[(*j)] == '\"')
			break ;
		(*j)++;
	}
	nav = ft_strdup(av);
	sfree(av);
	av = ft_strjoin(nav, ft_substr(str, start, (*j) - start));
	sfree(nav);
	return (av);
}

/*****************************************************************************
*Checks str (already initiated woth or without quotes) looking for new quotes*
*	at any point of the string.                                              *
*Then removes it, and returns a clean string, ready for parsing.             *
*****************************************************************************/
char	*ms_quote_loop(char *av, int *j, char *str, t_token *tk)
{
	int		start2;
	char	*nav;

	start2 = 0;
	nav = NULL;
	if (str[(*j)] == '\'' || str[(*j)] == '\"')
	{
		start2 = (*j) + 1;
		(*j) = end_quote(str, (*j) + 1, str[(*j)], tk);
		if ((*j) == -1)
			return (NULL);
		nav = ft_strdup(av);
		sfree(av);
		av = ft_strjoin(nav, ft_substr(str, start2, (*j) - start2));
		(*j)++;
	}
	else
		av = ms_quote_loop_sub(str, j, av);
	if (str[(*j)] && (str[(*j)] != ' ' && str[(*j)] != '\0'))
	{
		av = ms_quote_loop(av, j, str, tk);
		if (!av)
			return (NULL);
	}
	return (av);
}
