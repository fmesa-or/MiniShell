/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:46:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 21:19:25 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esto cuenta la cantidad de filas de un array doble*/
int	array_count(char **av)
{
	int i;

	i = 0;
	while(av[i])
		i++;
	return(i);
}

/*a esta ft del echo tendremos q pasarle los argumentos q se le pasaran,
se ponen en array doble para facilitar na mas*/
int	ft_echo(char **argv)
{
	int	i;
	int n_flag;

	printf("echo RAMON\n");
	n_flag = 0;
	i = 1;
	if(array_count(argv) > 1)
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			n_flag = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] == '\0')
				write(1, " ", 1);
			i++;
		}
		
	}
	if(n_flag == 0)
		write(1, "\n", 1);
	return(1);
}


/*Esta funcion busca e imprime el PWD, lo he cambiado
	para q no tengamos q recurrir a nuestra lista,
	de manera q siempre lo escriba*/

/*int ft_pwd(t_data *data)
{
	char	*aux;

	aux = getcwd(NULL, 0);
	if (write(1,aux, sizeof(aux)) == -1)
		return (-1);
	sfree(aux, data);
	if (write(1, "\n", 1) == -1)
		return (-1);
	return (0);
}*/

/*Esta funcion es para sacar el env actual por pantalla;
	Convierte nuestra lista en un char ** y lo imprime linea a linea
	¡¡Revisar si necesita salto de linea!!*/

int	ft_env(t_list *list)
{
	while (list)
	{
		if (write(1,list->key,ft_strlen(list->key)) == -1)
			return (-1);
		if (list->value)
		{
			if (write(1, "=", 1) == -1)
				return (-1);
			if (write(1,list->value,ft_strlen(list->value)) == -1)
				return (-1);
		}
		if (write(1, "\n", 1) == -1)
			return (-1);
		list = list->next;
	}
	return (0);
}
