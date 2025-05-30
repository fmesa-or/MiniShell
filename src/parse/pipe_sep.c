/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_separator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:29:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 17:50:14 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_separator_sub(int i, char *str, char **av, int *k)
{
	int	start;

	start = i;
	i = pipe_iteri(str, start, '|');
	av[(*k)] = ft_substr(str, start, i - start);
	if (str[i] == '|')
	{
		if (!str[i + 1])
		{
			(*k)++;
			av[(*k)] = ft_strdup("");
		}
		i++;
	}
	return (i);
}

/*****************************************************************************
*This function takes the initial string passed to it and splits it by pipes. *
*Returns char **, corresponding to argv.                                     *
*It takes into account single quotes, double quotes, and backslash.          *
*The redirection handling will have to be done before or after this function.*
*****************************************************************************/
char	**pipe_separator(char *str, t_data *data)
{
	char	**av;
	int		k;
	int		npipe;
	int		i;

	k = 0;
	i = 0;
	npipe = pipe_count(str);
	av = smalloc(sizeof(char *) * (npipe +1));
	if (!av)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes",
			NULL, data);
		sexit(errno);
	}
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		i = pipe_separator_sub(i, str, av, &k);
		k++;
	}
	av[k] = NULL;
	return (av);
}
