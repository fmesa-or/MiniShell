/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/07 15:06:02 by rmarin-j         ###   ########.fr       */
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
    while (list)
    {
        write(1, "declare -x ", 11);
        write(1, list->key, ft_strlen(list->key));
		write(1, "=\"", 2);
		if(list->value)
			write(1, list->value, ft_strlen(list->value));
		write(1, "\"\n", 2);
        list = list->next;
    }
    
}

/*Esta funcion va a crear y modificar keys y sus values segun el argumento q se le pase
Tendra q ser llamada dentro de un while para que se le vayan pasando los args con indice*/

int	ft_export(t_list *list, char *n_key)
{
	char	**aux;
	t_list	*node;

	if (n_key[0] == '=')
		return (-1);
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
	return (0);
}		


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
