/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:55:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 15:34:07 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_key_sub(t_list *aux)
{
	sfree(aux->value);
	sfree(aux->key);
	sfree(aux);
	return ;
}

static void	clear_key(t_list *list, char *key)
{
	t_list	*aux;
	t_list	*prev;

	aux = list;
	if (ft_strcmp((list)->key, key) == 0)
	{
		list = list->next;
		clear_key_sub(aux);
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
		clear_key_sub(aux);
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
