/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/02 20:18:12 by fmesa-or         ###   ########.fr       */
=======
/*   Updated: 2024/10/22 15:39:19 by rmarin-j         ###   ########.fr       */
>>>>>>> export
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

<<<<<<< HEAD
/*esta funcion busca un caracter dentro de un str y devuelve el indice donde lo encuentra.
Sino lo encuentra devuelve -1;*/

int ft_strchr(const char *str, char c)
{
	char	*p;
	int	 i;

	i = 0;
	p = (char *)str;
	while (p[i] != c && p[i] != '\0')
		i++;
	if (p[i] == c)
		return (i);
	return (-1);
}

=======
>>>>>>> export
/*Esta funcion imprime por pantalla el env con "declare -x" antes de cada linea*/

void	ft_voidexport(t_list *list)
{
<<<<<<< HEAD
	char	**env;
	int	 i;

	i = 0;
	env = listtoenv(list);
	while (env)
	{
		write(1, "declare -x ", 11);
		write(1, &env[i], ft_strlen(env[i]));
		i++;
	}
		
=======
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
    
>>>>>>> export
}

/*Esta funcion va a crear y modificar keys y sus values segun el argumento q se le pase
Tendra q ser llamada dentro de un while para que se le vayan pasando los args con indice*/

<<<<<<< HEAD
void	ft_export(t_list *list, char *n_key)
=======
int	ft_export(t_list *list, char *n_key)
>>>>>>> export
{
	char	**aux;
	t_list	*node;

<<<<<<< HEAD
	i = 0;
	if (ft_strchr(n_key, '=') == -1)
	{
		while (ft_strcmp(list->key, n_key) != 0 || list->next != NULL)
			list = list->next;
		//crea nuevo elemento y list->key se convierte en n_key
	}
/* 	if (ft_strchr(n_key, '=') == -1)//si el igual esta en el 0 no deberia valer?
		mensaje error; */
	else
	{
		aux = ft_split(n_key, '=');
		while (ft_strcmp(list->key, aux[i]) != 0 || list->next != NULL)
			list = list->next;
		
	}
		
=======
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
>>>>>>> export


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
