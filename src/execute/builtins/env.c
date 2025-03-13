/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:08:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/03/11 14:15:37 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*Necesaria para la ejecución.(execev)
*/
char	**ms_return_env(t_data *data)
{
	t_list	*list;
	char	**env;
	char	*aux;
	int		i;

	i = 0;
	list = data->exported_list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	list = data->exported_list;
	i = -1;
	while (list)
	{
		aux = ft_strjoin(list->key, "=");
		env[++i] = ft_strjoin(aux, list->value);
		free(aux);
		list = list->next;
	}
	env[++i] = NULL;
	return (env);
}

/*
*Esta funcion es para sacar el env actual por pantalla;
*	Convierte nuestra lista en un char ** y lo imprime linea a linea
*	¡¡Revisar si necesita salto de linea!!
*/
int	bi_env(t_data *data, t_token *token)
{
	char	**env;
	int		i;
	
	env = ms_return_env(data);
	i = 0;
	while (env[i])
	{
	//	if (ft_strncmp(env[i], "minishell", 9) == 0)//ESTAMOS ALMACENANDO EN ENV UN DATO FIANL MAL!!
	//		break;
		if (write(token->fd[1], env[i], ft_strlen(env[i])) == -1)
			return (-1);
		if (write(token->fd[1], "\n", 1) == -1)
			return (-1);
		i++;
	}
	return (0);

/*  V0.1
	while (list)
	{
		if (write(1, list->key, ft_strlen(list->key)) == -1)
			return (-1);
		if (list->value)
		{
			if (write(1, "=", 1) == -1)
				return (-1);
			if (write(1, list->value, ft_strlen(list->value)) == -1)
				return (-1);
		}
		if (write(1, "\n", 1) == -1)
			return (-1);
		list = list->next;
	}
	return (0);*/
}
