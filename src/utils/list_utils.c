/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/13 14:11:08 by rmarin-j         ###   ########.fr       */
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
		free(aux->value);
		free(aux->key);
		free(aux);
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
		free(aux->value);
		free(aux->key);
		free(aux);
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

	node = malloc(sizeof(t_list));
	if (!node)
	{
		throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		exit(errno);
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

