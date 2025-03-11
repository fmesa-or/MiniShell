/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/11 14:09:27 by fmesa-or         ###   ########.fr       */
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

char **listtoenv(t_list *list)
{
    char    **env;
    int     i;
	t_list	*head;

    
    i = 0;
	head = list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = malloc(sizeof(char *) * i + 1);
	if (!env)
		throw_error("ERROR: ", NULL, NULL);
	i = 0;
	list = head;
    while (list)
    {
        env[i] = ft_strcjoin(list->key, list->value, '=');
        i++;
        list = list->next;
    }
	env[i] = NULL;
    return(env);

}

t_list	*envtolist(char **env)
{
    t_list *list;
	t_list *head;
    char    **aux;
    int     i;

	if (!env || !*env)
		return (NULL);
	list = NULL;
	head =NULL;
	aux = NULL;
	i = 0;
    while (env[i])
    {
        aux = ft_split(env[i], '=');
		if (list == NULL)
		{
			list =ft_lstnew(aux[0],aux[1]);
			head = list;
		}
		else
		{
			list->next =ft_lstnew(aux[0],aux[1]);
        	list = list->next;
		}
        i++;
    }
	free_2ptr(aux);
	return (head);
}

/*Esta funcion añade un nodo nuevo al final de la lista,
añadiendo solo su key y value*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		while (*lst)
		{
			if ((*lst)->next)
				(*lst) = (*lst)->next;
			else
				break ;
		}
		(*lst)->next = new;
	}
}


t_list	*ft_lstnew(char *n_key, char *n_value)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	printf("CHECK lstnew n_key: %s\n", n_key);
	printf("CHECK lstnew n_value: %s\n", n_value);
	node->key = n_key;
	node->value = n_value;
	printf("CHECK lstnew node->key: %s\n", node->key);
	printf("CHECK lstnew node->value: %s\n", node->value);
	node->next = NULL;
	return (node);
}
