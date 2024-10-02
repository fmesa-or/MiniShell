/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:19:01 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 20:13:27 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(t_varlist *list, char *key)
{
	if (*key == ' ')
		return (ft_strdup("$ "));
	if (*key == '\0')
		return (ft_strdup("$"));
	while (list)
	{
		if (!ft_strcmp(list->key, key))
			return (ft_strdup(list->value));
		list = list->next;
	}
	return (NULL);
}
