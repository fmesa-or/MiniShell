/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/02 18:23:56 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*esta funcion busca un caracter dentro de un str y devuelve el indice donde lo encuentra.
Sino lo encuentra devuelve -1;*/

int ft_strchr(const char *str, char c)
{
	char	*p;
    int     i;

    i = 0;
	p = (char *)str;
	while (p[i] != c && p[i] != '\0')
		i++;
	if (p[i] == c)
		return (i);
	return (-1);
}

/*Esta funcion imprime por pantalla el env con "declare -x" antes de cada linea*/

void    ft_voidexport(t_list *list)
{
    char    **env;
    int     i;

    i = 0;
    env = listtoenv(list);
    while (env)
    {
        write(1, "declare -x ", 11);
        write(1, &env[i], ft_strlen(env[i]));
        i++;
    }
    
}

/*Esta funcion va a crear y modificar keys y sus values segun el argumento q se le pase
Tendra q ser llamada dentro de un while para que se le vayan pasando los args con indice*/

int	ft_export(t_list *list, char *n_key)
{
	char	**aux;
	t_list	*node;

	if (n_key[0] == '=')
		//ft_error
	aux = ft_split (n_key, '=');
	node = find_key(list, aux[0]);
	if (node)
	{
		if (aux[1])
			node->value = aux[1];
	}
	else
		ft_lstadd_back(&list, ft_lstnew(aux[0], aux[1]));
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

/*     if (ft_strchr(n_key, '=') == -1)
    {
        while (ft_strcmp(list->key, n_key) != 0 || list->next != NULL)
            list = list->next;
		ft_lstnew(list, n_key);
		list->value = NULL;
		return (0);
    }
	else
	{
		aux = ft_split(n_key, "=");
		list = find_key(list, aux[0]);
		if (!list)
		{
			ft_lstnew(list, aux[0]);
			list->value = aux[1];
		}
		else
		{
			if (list->value)
				free(list->value);
			list->value = aux[1];
		}
	} */


/*Esta funcion busca dentro de la lista donde se encuentra una key
y retorna el nodo en el que esta o null si no lo encuetra*/

t_list	*find_key(t_list *list, char *n_key)
{
	while (list->next != NULL)
	{
		if (ft_strcmp(list->key, n_key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
