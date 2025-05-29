/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/29 19:29:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************************************************
* This function removes a node from our list, which needs to be passed *
* with &, since it uses double pointer.                                *
***********************************************************************/
void	ft_unset(t_list **list, char *ref)
{
	t_list	*aux;
	t_list	*prev;

	aux = *list;
	if (ft_strcmp((*list)->key, ref) == 0)
	{
		*list = (*list)->next;
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

/***********************************************************************
* This function adds a new node at the end of a t_list.                *
***********************************************************************/
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
	t_list	*node;

	node = smalloc(sizeof(t_list));
	if (!node)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);
		sexit(errno);
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
