/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:25:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 16:59:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************************************
*Writes an ERROR message when command is not found and returns last status.*
***************************************************************************/
int	ms_cmd_nf(char *cmd)
{
	write(2, "Minishell: ", 11);
	write(2, cmd, sizeof(cmd));
	write(2, ": command not found", 19);
	return (127);
}

/***************************
*If c is a number returns 0*
***************************/
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*****************************************************************************
*Finds a node in a list with the key of the enviroment variable (like "PATH")*
*****************************************************************************/
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