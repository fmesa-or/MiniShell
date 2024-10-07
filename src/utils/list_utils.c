/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/06 19:05:14 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_unset(t_list **list, char *ref)
{
    t_list  *aux;

    aux = *list;
	if (ft_strcmp((*list)->key, ref) == 0)
	{
		*list =(*list)->next;
		free(aux->value);
		free(aux->key);
		free(aux);
		return ;
	}
    while (ft_strcmp((*list)->key, ref) != 0 || !list)
    {
        aux = *list;
        (*list) = (*list)->next;
    }
	write(1, "llega2\n", 8);
	if (*list && ft_strcmp((*list)->key, ref) == 0)
	{
		aux = (*list)->next;
		free((*list)->value);
		free((*list)->key);
		free((*list));
		write(1, "llega3\n", 8);
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
		throw_error("ERROR: ");
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

t_list  *envtolist(char **env)
{
    t_list *list;
    int     i;
	t_list *head;
    char    **aux;

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
	return (head);
}

/*Esta funcion añade un nodo nuevo al final de la lista,
añadiendo solo su key y value*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

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
		temp = (*lst);
		temp->next = new;
	}
}


t_list	*ft_lstnew(char *n_key, char *n_value)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->key = n_key;
	node->value = n_value;
	node->next = NULL;
	return (node);
}
