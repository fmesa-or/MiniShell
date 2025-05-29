/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtolist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:47:46 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 19:31:39 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	envtolist_sub(char **aux)
{
	if (!aux || !aux[0])
	{
		free_2ptr(aux);
		throw_error("ERROR: Split failed.", NULL, NULL);
	}
}

t_list	*envtolist(char **env, t_list *list, t_list *head, char **aux)
{
	int	i;

	if (!env || !*env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		aux = ft_split(env[i], '=');
		envtolist_sub(aux);
		if (list == NULL)
		{
			list = ft_lstnew(aux[0], aux[1]);
			head = list;
		}
		else if (env[i + 1])
		{
			list->next = ft_lstnew(aux[0], aux[1]);
			list = list->next;
		}
		i++;
	}
	free_2ptr(aux);
	return (head);
}
