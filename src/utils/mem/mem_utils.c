
#include "minishell.h"

void	sexit(int code)
{
	sclose(STDIN_FILENO);
	sclose(STDOUT_FILENO);
	sclose(STDERR_FILENO);
	sclose_all();
	sfree_all();
	exit(code);
}

void	alloc_fail(int type)
{
	if (type == NO_MEMORY)
		write(2, "CATASTROPHIC - No memory left on the device\n", 45);
	if (type == DUP_FAIL)
		write(2, "CATASTROPHIC - Error duplicating file descriptor\n", 50);
	if (type == DUP2_FAIL)
		write(2, "CATASTROPHIC - Error duplicating file descriptor\n", 50);
	if (type == PIPE_FAIL)
		write(2, "CATASTROPHIC - Pipe failed\n", 28);
	sexit(1);
}

/****************************************************
*When called with data, stores it in a static.access*
*When called with NULL, returns data.               *
****************************************************/
t_data	*get_pdata(t_data *data)
{
	static t_data	*pdata;

	if (data)
		pdata = data;
	return (pdata);
}

/************************************************
*Sets the memory for b pointer with int c value.*
************************************************/
void	*ft_memset(void *b, int c, int len)
{
	unsigned char	*p;

	p = b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}

char	*get_cwd()
{
	char	*tmp;
	char	*path;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp);
	free(tmp);
	if (!path)
		alloc_fail(NO_MEMORY);
	return (path);
}