/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:29:49 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_all *data)
{
	t_varlist	*list;

	list = data->exported_list;
	while (list)
	{
		if (list->key && list->value)
		{
			write(1, list->key, ft_strlen(list->key));
			write(1, "=", 1);
			write(1, list->value, ft_strlen(list->value));
			write(1, "\n", 1);
		}
		list = list->next;
	}
	return (1);
}

char	**ft_return_env(t_all *data)
{
	t_varlist	*list;
	char		**env;
	int			i;
	char		*aux;

	i = 0;
	list = data->exported_list;
	while (list)
	{
		i++;
		list = list->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	list = data->exported_list;
	i = 0;
	while (list)
	{
		aux = ft_strjoin(list->key, "=", 0, 0);
		env[i] = ft_strjoin(aux, list->value, 1, 0);
		i++;
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}
