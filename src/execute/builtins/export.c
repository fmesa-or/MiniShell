/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/05 12:43:09 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion busca dentro de la lista donde se encuentra una key
y retorna el nodo en el que esta o null si no lo encuetra*/

t_list	*find_key(t_list *list, char *n_key)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, n_key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

/******************************************************************************
*This function prints the env to the screen with "declare -x" before each line*
******************************************************************************/
void	bi_voidexport(t_list *list)
{
	while (list)
	{
		write(1, "declare -x ", 11);
		write(1, list->key, ft_strlen(list->key));
		write(1, "=\"", 2);
		if (list->value)
			write(1, list->value, ft_strlen(list->value));
		write(1, "\"\n", 2);
		list = list->next;
	}

}

/*
*This function will create and modify keys and their values according to the argument passed to it
must be called within a while loop so that the args with index are passed to it*/
int	bi_export(t_list *list, char *n_key)//(t_list, VARIABLE="HOLA")
{
	char	**aux;
	t_list	*node;

	if (!n_key)
	{
		bi_voidexport(list);
		return (0);
	}
	if (n_key[0] == '=')
		return (-1);
	aux = ft_split (n_key, '=');
	node = find_key(list, aux[0]);
	if (node)
	{
		if (aux[1])
			node->value = aux[1];
	}
	else
		ft_lstadd_back(&list, ft_lstnew(aux[0], aux[1]));
	return (0);
}
