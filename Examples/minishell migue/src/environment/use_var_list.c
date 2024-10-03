/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:19:01 by jholland          #+#    #+#             */
/*   Updated: 2024/10/03 11:45:48 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_mj.h"

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
