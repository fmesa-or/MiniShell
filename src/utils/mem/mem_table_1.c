
#include "minishell.h"

void	*smalloc(long bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		alloc_fail(NO_MEMORY);
	mem_add(ptr);
	return (ptr);
}

void	sfree(void *ptr)
{
	mem_delete(ptr);
}

void	sfree_all()
{
	mem_clear();
}

int	sopen(const char *file, int oflag, int perm)
{
	t_data	*data;
	int		fd;

	data = get_pdata(NULL);
	if (!data)
		return (-1);
	fd = -1;
	if (perm == -1)
		fd = open(file, oflag);
	else
		fd = open(file, oflag, perm);
	if (fd >= 0 && fd < 1024)
		data->fd_table[fd] = 1;
	return (fd);
}