/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:55:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 19:30:04 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_key(t_list *list, char *key)
{
	t_list	*aux;
	t_list	*prev;

	aux = list;
	if (ft_strcmp((list)->key, key) == 0)
	{
		list = list->next;
		free(aux->value);
		free(aux->key);
		free(aux);
		return ;
	}
	while (aux && ft_strcmp(aux->key, key) != 0)
	{
		prev = aux;
		aux = aux->next;
	}
	if (aux && ft_strcmp(aux->key, key) == 0)
	{
		if (aux->next == NULL)
			prev->next = NULL;
		else
			prev->next = aux->next;
		free(aux->value);
		free(aux->key);
		free(aux);
	}
}

int	bi_unset(t_list *list, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
		clear_key(list, argv[i++]);
	return (0);
}
