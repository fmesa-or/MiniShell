/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:08:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 16:36:25 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_miscelaneus(char *key, char *value)
{
	char	*aux;
	char	*aux2;

	aux = ft_strjoin(key, "=");
	if (!value)
		aux2 = ft_strjoin(aux, "");
	else
		aux2 = ft_strjoin(aux, value);
	free (aux);
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
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
	{
		throw_error("ERROR: malloc failed in ms_return_env", NULL, data);
		exit(errno);
	}
	list = data->exported_list;
	i = -1;
	while (list)
	{
		env[++i] = str_miscelaneus(list->key, list->value);
		list = list->next;
	}
	env[++i] = NULL;
	return (env);
}

/**********************************************
*Prints the whole enviroment.                 *
*Turns the list in a char array and prints it.*
**********************************************/
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
		printf("%s\n", env[i]);
		if (write(token->fd[1], env[i], ft_strlen(env[i])) == -1)
			return (-1);
		if (write(token->fd[1], "\n", 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

