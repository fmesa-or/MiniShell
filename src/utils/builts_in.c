/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:46:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/19 19:21:55 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion busca e imprime el PWD, lo he cambiado
	para q no tengamos q recurrir a nuestra lista,
	de manera q siempre lo escriba*/

void ft_pwd()
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

/*replica funcion cd. Hay q pasarle los argv siendo el primero el mismo comando cd*/
int	ft_cd(char **argv, t_list *env)
{
	int	cd_stat;

	cd_stat = 0;
	if (argv[2])
		throw_error("ERROR:");
	else
	{
		ft_export(env, ft_strcjoin("OLDPWD", getcwd(NULL, 0), '='));
		cd_stat= chdir(argv[1]);
		if(cd_stat != 0)
			throw_error("ERROR: no find rute");
		else
			ft_export(env, ft_strcjoin("PWD", getcwd(NULL, 0), '='));
	}
	return(cd_stat);
}