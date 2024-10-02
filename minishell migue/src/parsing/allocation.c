/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:46:28 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:25 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_var(t_all *data, char **str, unsigned int *len)
{
	unsigned int	*var_len;

	var_len = var_lengths(data, *str);
	*len += var_len[1];
	*str += var_len[0];
	free(var_len);
}

char	*parsed_allocation(t_all *data, char *str)
{
	unsigned int	len;
	int				esc;
	char			quoted;

	esc = 0;
	quoted = '\0';
	len = 0;
	while (*str)
	{
		if (!esc && !quoted && (*str == '\"' || *str == '\''))
			quoted = *str;
		else if (!esc && quoted && quoted == *str)
			quoted = '\0';
		else if (!esc && !quoted && *str == '\\')
			esc = 1;
		else if (!esc && quoted != '\'' && *str == '$')
			skip_var(data, &str, &len);
		else
		{
			esc = 0;
			len++;
		}
		str++;
	}
	return (malloc(len + 1));
}
