/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:10:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 20:24:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_lstat(char *str, int i, t_data *data)
{
	int		n;
	char	*stat;
	char	*aux;
	char	*sub;

	n = i;
	stat = ft_itoa(data->l_status);
	sub = ft_substr(str, 0, n);
	aux = ft_strjoin(sub, stat);
	sfree(sub);
	sfree(stat);
	sub = ft_substr(str, n + 2, ft_strlen(str));
	stat = ft_strjoin(aux, sub);
	sfree(aux);
	sfree(sub);
	return (stat);
}
