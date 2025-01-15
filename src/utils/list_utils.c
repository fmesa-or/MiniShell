/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/02 20:13:42 by fmesa-or         ###   ########.fr       */
=======
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:08:37 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/12/05 16:13:04 by rmarin-j         ###   ########.fr       */
>>>>>>> export
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*Esta funcion elimina un nodo de nuestra lista, q necesita
q la pasemos con &, ya que usa doble puntero*/

<<<<<<< HEAD
t_list	*ft_unset(t_list *list, char *ref)
{
	t_list	*aux;
	t_list	*aux2;

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
=======
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
>>>>>>> export
}

char **listtoenv(t_list *list)
{
<<<<<<< HEAD
	char	**env;
	int		i;

		
	i = 0;
	env = NULL;
	while (list)
	{
		env[i] = ft_strcjoin(list->key, list->value, '=');
		i++;
		list = list->next;
	}
	return(env);
=======
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
>>>>>>> export

}

t_list	*envtolist(char **env)
{
<<<<<<< HEAD
	t_list	*list;
	int		i;
	char	**aux;

	i = 0;
	list = NULL;
	while (env[i])
	{
		aux = ft_split(env[i], '=');
		list->key = aux[0];
		list->value = aux[1];
		list = list->next;
		i++;
	}
	return (list);
=======
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
>>>>>>> export
}
