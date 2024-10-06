/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/06 16:00:48 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list  *ft_unset(t_list *list, char *ref)
{
    t_list  *aux;
    t_list  *aux2;

    aux = list;
    while (ft_strcmp(list->key, ref) != 0)
    {
        aux->next = list;
        list = list->next;
    }
    aux2 = list->next;
    aux->next = aux2;
    free(list->value);
    free(list->key);
    free(list);
    return (aux);
}

char **listtoenv(t_list *list)
{
    char    **env;
    int     i;

    
    i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = malloc(sizeof(char *) * i + 1);//proteccion
	i = 0;
    while (list)
    {
		write(1, "pito\n", 5);
        env[i] = ft_strcjoin(list->key, list->value, '=');
        i++;
        list = list->next;
    }
	env[i] = 0;
    return(env);

}

t_list  *envtolist(char **env)
{
    t_list *list;
    int     i;
	t_list *head;
    char    **aux;

if (!env || !*env) return (NULL);
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
		}
        //list->key = aux[0];
        //list->value = aux[1];
        list = list->next;
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
