/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:46:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/04 14:03:22 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion busca e imprime el PWD asociado al value de dicha key
	dentro de NUESTRA LISTA, por lo que tendremos q actualizar dicho value
	cada vez que usemos el cmd CD!!!*/

void ft_pwd(t_list *list)
{
	find_key(list, "PWD");
	write(1, &list->value, ft_strlen(list->value));
	write(1, "\n", 1);
}

/*Esta funcion es para sacar el env actual por pantalla;
	Convierte nuestra lista en un char ** y lo imprime linea a linea
	¡¡Revisar si necesita salto de linea!!*/

void	ft_env(t_list *list)
{
	int		i;
	char	**env;

	i = 0;
	env = listtoenv(list);
	while (env[i])
	{
		write (1, &env[i], ft_strlen(env[i]));
		i++;
	}
}
