/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:06:25 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/30 13:27:57 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_get_nq_sub(char *str, char *av, int *j, t_token *tk)
{
	char	*nav;
	int		start;

	nav = NULL;
	start = (*j) + 1;
	(*j) = end_quote(str, (*j) + 1, str[(*j)], tk);
	if ((*j) == -1)
		return (NULL);
	nav = ft_strdup(av);
	sfree(av);
	av = ft_strjoin(nav, ft_substr(str, start, (*j) - start));
	(*j)++;
	return (av);
}

/**************************************************************************
*Subdivision for get_argv(), called when the string starts without quotes.*
*Checks if it has quotes inside the str.                                  *
*Returns the av ready for being stored.                                   *
**************************************************************************/
char	*ms_get_argv_nquotes(char *str, int *j, char *av, t_token *tk)
{
	int	start;

	start = (*j);
	while (str[(*j)] && (!ft_isspace(str[(*j)])))
	{
		if (str[(*j)] == '\'' || str[(*j)] == '\"')
			break ;
		(*j)++;
	}
	av = ft_substr(str, start, (*j) - start);
	if (str[(*j)] == '\'' || str[(*j)] == '\"')
		av = ms_get_nq_sub(str, av, j, tk);
	if (!av)
		return (NULL);
	if (str[(*j)] && (str[(*j)] != ' ' && str[(*j)] != '\0'))
	{
		av = ms_quote_loop(av, j, str, tk);
		if (!av)
			return (NULL);
	}
	return (av);
}

/************************************************************************
*Saves a substring separated with blanks from the main str and stores it*
*	inside a list for parsing argv.                                     *
*Returns the actual position (int) of the blank space.                  *
************************************************************************/
int	get_av(t_list **lst, char *str, int j, t_token *tk)
{
	int		start;
	char	*av;

	start = j;
	if (str[j] == '\'' || str[j] == '\"')
	{
		j = end_quote(str, j + 1, str[j], tk);
		if (j == -1)
			return (-1);
		av = ft_substr(str, start + 1, ++j - (start + 2));
		if (str[j] && (str[j] != ' ' && str[j] != '\0'))
		{
			av = ms_quote_loop(av, &j, str, tk);
			if (!av)
				return (-1);
		}
		if (ft_strlen(av) == 2)
			return (j);
	}
	else
		av = ms_get_argv_nquotes(str, &j, NULL, tk);
	if (!av)
		return (-1);
	ft_lstadd_back(lst, ft_lstnew(av, NULL));
	return (j);
}
