/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:35:32 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 12:08:28 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



unsigned int	hash_index_ptr(void *ptr)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	addr = ~addr + (addr << 15);
	addr = addr ^ (addr >> 12);
	addr = addr + (addr << 2);
	addr = addr ^ (addr >> 4);
	addr = addr * 2057;
	addr = addr ^ (addr >> 16);

	return (addr % MEM_HASH_SIZE);
}

void	alloc_fail(int type, t_data *data)
{
	if (type == NO_MEMORY)
		write(2, "CATASTROPHIC - No memory left on the device\n", 45);
	if (type == DUP_FAIL)
		write(2, "CATASTROPHIC - Error duplicating file descriptor\n", 50);
	if (type == DUP2_FAIL)
		write(2, "CATASTROPHIC - Error duplicating file descriptor\n", 50);
	if (type == PIPE_FAIL)
		write(2, "CATASTROPHIC - Pipe failed\n", 28);
	sexit(1, data);
}

int	spipe(int *fd, t_data *data)
{
	if (pipe(fd) == -1)
		alloc_fail(PIPE_FAIL, data);

	data->fd_table[fd[0]] = 1;
	data->fd_table[fd[1]] = 1;
	return (0);
}


int	sclose(int fd, t_data *data)
{
	if (fd < 0 || fd > 1023)
		return (1);
	data->fd_table[fd] = 0;
	return (close(fd));
}

void	sclose_all(t_data *data)
{
	int	fd;

	fd = 0;
	while (fd < 1024)
	{
		if (data->fd_table[fd])
		{
			close(fd);
			data->fd_table[fd] = 0;
		}
		fd++;
	}
}
