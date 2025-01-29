/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:25:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 19:04:53 by fmesa-or         ###   ########.fr       */
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
