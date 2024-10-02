/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:11:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/02 20:18:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

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

/*Esta funcion imprime por pantalla el env con "declare -x" antes de cada linea*/

void	ft_voidexport(t_list *list)
{
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
		
}

/*Esta funcion va a crear y modificar keys y sus values segun el argumento q se le pase
Tendra q ser llamada dentro de un while para que se le vayan pasando los args con indice*/

void	ft_export(t_list *list, char *n_key)
{
	char	**aux;
	int		i;

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
		

}

