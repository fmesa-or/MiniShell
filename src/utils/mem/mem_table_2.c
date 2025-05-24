
#include "minishell.h"

int	sclose(int fd)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (!data || fd < 0 || fd > 1023)
		return (1);
	data->fd_table[fd] = 0;
	return (close(fd));
}

void	sclose_all(void)
{
	t_data	*data;
	int		fd;

	data = get_pdata(NULL);
	if (!data)
		return;
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

int	sdup(int fd)
{
	t_data	*data;
	int		new_fd;

	data = get_pdata(NULL);
	if (!data || fd < 0)
		return (-1);
	new_fd = dup(fd);
	if (new_fd == -1)
		alloc_fail(DUP_FAIL);
	data->fd_table[new_fd] = 1;
	return (new_fd);
}

int	sdup2(int fd1, int fd2)
{
	t_data	*data;
	int		new_fd;

	data = get_pdata(NULL);
	new_fd = -1;
	if (!data || fd1 == -1)
		return (new_fd);
	if (fd1 == fd2)
		return (0);
	new_fd = dup2(fd1, fd2);
	if (new_fd == -1)
		alloc_fail(DUP2_FAIL);
	data->fd_table[new_fd] = 1;
	return (new_fd);
}

int	spipe(int *fd)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (!data)
		return (1);
	if (pipe(fd) == -1)
		alloc_fail(PIPE_FAIL);
	data->fd_table[fd[0]] = 1;
	data->fd_table[fd[1]] = 1;
	return (0);
}