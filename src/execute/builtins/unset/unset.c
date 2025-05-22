/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:55:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 21:17:35 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_key(t_list *list, char *key, t_data *data)
{
	t_list	*aux;
	t_list	*prev;

	aux = list;
//	dprintf(2, RD"CHECK\n"RES);
	if (ft_strcmp((list)->key, key) == 0)
	{
		list = list->next;
		sfree(aux->value, data);
		sfree(aux->key, data);
		sfree(aux, data);
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
		sfree(aux->value, data);
		sfree(aux->key, data);
		sfree(aux, data);
	}
}

int	bi_unset(t_list *list, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
		clear_key(list, argv[i++], data);
	return (0);
}
