/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:21:27 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:20 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_key(t_all *data, char *key)
{
	t_varlist	*node;
	t_varlist	*prev;
	t_varlist	*next;

	node = data->exported_list;
	prev = NULL;
	while (node)
	{
		next = node->next;
		if (!ft_strcmp(node->key, key))
		{
			if (prev)
				prev->next = next;
			else
				data->exported_list = next;
			prev = node;
			free(node->key);
			free(node->value);
			free(node);
		}
		else
			prev = node;
		node = next;
	}
}

int	ft_unset(t_all *data, char **argv)
{
	int			i;

	i = 1;
	while (argv[i])
		clear_key(data, argv[i++]);
	return (0);
}
