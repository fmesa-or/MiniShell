/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:58:22 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 20:58:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sopen(const char *file, int oflag, int perm, t_data *data)
{
	int	fd;

	fd = -1;
	if (perm == -1)
		fd = open(file, oflag);
	else
		fd = open(file, oflag, perm);

	if (fd >= 0 && fd < 1024)
		data->fd_table[fd] = 1;

	return (fd);
}

void	sexit(int code, t_data *data)
{
	sclose(STDIN_FILENO, data);
	sclose(STDOUT_FILENO, data);
	sclose(STDERR_FILENO, data);

	sclose_all(data);
	sfree_all(data);
	exit(code);
}
