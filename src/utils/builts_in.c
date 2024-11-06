/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:46:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/06 20:22:47 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion busca e imprime el PWD asociado al value de dicha key
	dentro de NUESTRA LISTA, por lo que tendremos q actualizar dicho value
	cada vez que usemos el cmd CD!!!*/

void ft_pwd(t_list *list)
{
	char	*aux;

	aux = getcwd(NULL, 0);
	write(1,aux, sizeof(aux));
	free(aux);
	write(1, "\n", 1);
}

/*Esta funcion es para sacar el env actual por pantalla;
	Convierte nuestra lista en un char ** y lo imprime linea a linea
	¡¡Revisar si necesita salto de linea!!*/

void	ft_env(t_list *list)
{
	while (list)
	{
		write(1,list->key,ft_strlen(list->key));
		if(list->value)
		{
			write(1,"=",1);
			write(1,list->value,ft_strlen(list->value));
		}
		write(1,"\n",1);
		list = list->next;
	}
}
/* Esto es version antigua de ft_env
	int		i;
	char	**env;

	i = 0;
	env = listtoenv(list);
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	} */