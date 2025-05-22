/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:56:26 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 12:02:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mem_del_sub(t_mem *prev, t_mem *mem, unsigned int i, t_data *data)
{
	if (prev)
		prev->next = mem->next;
	else
		data->mem_table[i] = mem->next;
	free(mem->ptr);
	free(mem);
	return ;
}

static void	mem_delete(void *ptr, t_data *data)
{
	unsigned int	index;
	t_mem			*mem;
	t_mem			*prev;

	if (!ptr)
		return ;

	index = hash_index_ptr(ptr);
	mem = data->mem_table[index];
	prev = NULL;

	while (mem)
	{
		if (mem->ptr == ptr)
		{
			mem_del_sub(prev, mem, index, data);
		}
		prev = mem;
		mem = mem->next;
	}
	free(ptr);
}



static void	mem_clear(t_data *data)
{
	unsigned int	index;
	t_mem			*mem;
	t_mem			*next;

	index = 0;
	while (index < MEM_HASH_SIZE)
	{
		if (data->mem_table[index])
		{
			mem = data->mem_table[index];
			while (mem)
			{
				next = mem->next;
				free(mem->ptr);
				free(mem);
				mem = next;
			}
			data->mem_table[index] = NULL;
		}
		index++;
	}
}

void	sfree(void *ptr, t_data *data)
{
	mem_delete(ptr, data);
}

void	sfree_all(t_data *data)
{
	mem_clear(data);
}
