/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:35:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 18:40:21 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	sdup(int fd, t_data *data)
{
	int	new_fd;

	new_fd = -1;
	if (fd >= 0 && (new_fd = dup(fd)) == -1)
		alloc_fail(DUP_FAIL, data);

	data->fd_table[new_fd] = 1;
	return (new_fd);
}

int	sdup2(int fd1, int fd2, t_data *data)
{
	int	new_fd;

	new_fd = -1;
	if (fd1 == -1)
		return (new_fd);
	if (fd1 == fd2)
		return (0);
	new_fd = dup2(fd1, fd2);
	if (new_fd == -1)
		alloc_fail(DUP2_FAIL, data);
	data->fd_table[new_fd] = 1;
	return (new_fd);
}

static t_mem	*mem_find(void *ptr, t_data *data)
{
	t_mem	*mem;

	if (!ptr)
		return (NULL);

	mem = data->mem_table[hash_index_ptr(ptr)];

	while (mem)
	{
		if (mem->ptr == ptr) return (mem);
		mem = mem->next;
	}

	return (NULL);
}


static void	mem_add(void *ptr, t_data *data)
{
	t_mem			*new_mem;
	t_mem			*new_node;
	unsigned int	index;

	if (!ptr)
		return ;
	new_mem = mem_find(ptr, data);
	if (new_mem)
	{
		free(new_mem->ptr);//revisar si es free o sfree
		new_mem->ptr = ptr;
	}
	else
	{
		index = hash_index_ptr(ptr) % MEM_HASH_SIZE;
		new_node = malloc(sizeof(t_mem));
		if (!new_node)
			alloc_fail(NO_MEMORY);

		new_node->ptr = ptr;
		new_node->next = data->mem_table[index];
		data->mem_table[index] = new_node;
	}
}

void	*smalloc(long bytes, t_data *data)//voy por aquí
{
	void	*ptr;

	if (!(ptr = malloc(bytes)))
		alloc_fail(NO_MEMORY, data);

	mem_add(ptr, data);
	return (ptr);
}
