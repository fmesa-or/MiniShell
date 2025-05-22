/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 12:08:19 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion elimina un nodo de nuestra lista, q necesita
q la pasemos con &, ya que usa doble puntero*/

void	ft_unset(t_list **list, char *ref)
{
	t_list  *aux;
	t_list	*prev;
	aux = *list;
 	if (ft_strcmp((*list)->key, ref) == 0)
	{
		*list =(*list)->next;
		sfree(aux->value);
		sfree(aux->key);
		sfree(aux);
		return ;
	}
	while (aux && ft_strcmp(aux->key, ref) != 0)
	{
		prev = aux;
		aux = aux->next;
	}
	if (aux && ft_strcmp(aux->key, ref) == 0)
	{
		prev->next = aux->next;
		sfree(aux->value);
		sfree(aux->key);
		sfree(aux);
	}
}

/*Esta funcion añade un nodo nuevo al final de un t_list */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current && current->next)
		current = current->next;
	current->next = new;
}


t_list	*ft_lstnew(char *n_key, char *n_value)
{
	t_list *node;

	node = smalloc(sizeof(t_list));
	if (!node)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		sexit(errno, data);
	}
	node->key = n_key;
	node->value = n_value;
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		count;

	count = 0;
	node = lst;
	while (node)
	{
		count++;
		node = node->next;
	}
		return (count);
}

