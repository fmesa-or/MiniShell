/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:25:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/03/26 13:42:38 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cmd_nf(char *cmd)
{
	write(2, "Minishell: ", 11);
	write(2, cmd, sizeof(cmd));
	write(2, ": command not found", 19);
	return (1);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

t_list	*find_key(t_list *list, char *n_key)
{
	while (list != NULL)
	{
		if (ft_strcmp(list->key, n_key) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}