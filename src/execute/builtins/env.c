/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:08:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 12:27:56 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_miscelaneus(char *key, char *value, t_data *data)
{
	char	*aux;
	char	*aux2;

	aux = ft_strjoin(key, "=", data);
	if (!value)
		aux2 = ft_strjoin(aux, "", data);
	else
		aux2 = ft_strjoin(aux, value, data);
	sfree(aux, data);
	return (aux2);
}

/****************
*Need for execve*
****************/
char	**ms_return_env(t_data *data)
{
	t_list	*list;
	char	**env;
	int		i;

	i = 0;
	list = data->exported_list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = smalloc(sizeof(char *) * (i + 1));
	if (!env)
	{
		throw_error("ERROR: smalloc failed in ms_return_env", NULL, data);
		sexit(errno, data);
	}
	list = data->exported_list;
	i = -1;
	while (list)
	{
		env[++i] = str_miscelaneus(list->key, list->value, data);
		list = list->next;
	}
	env[++i] = NULL;
	return (env);
}

/**********************************************
*Prints the whole enviroment.                 *
*Turns the list in a char array and prints it.*
**********************************************/
int	bi_env(t_data *data, t_token *token, int *fd)
{
	char	**env;
	int		i;

	env = ms_return_env(data);
	i = 0;
	while (env[i])
	{
	//	if (ft_strncmp(env[i], "minishell", 9) == 0)//ESTAMOS ALMACENANDO EN ENV UN DATO FIANL MAL!!
	//		break;
//		printf("%s\n", env[i]);
		if (write(fd[1], env[i], ft_strlen(env[i])) == -1)
			return (-1);
		if (write(fd[1], "\n", 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

