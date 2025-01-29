/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:08:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 14:19:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
