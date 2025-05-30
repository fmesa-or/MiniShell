/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 20:03:46 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_check_built_nspipe(t_token token)
{
	if (ft_strncmp(token.argv[0], "cd", ft_strlen(token.argv[0])) == 0)
		return (0);
	else if (ft_strncmp(token.argv[0], "unset", ft_strlen(token.argv[0])) == 0)
		return (0);
	else if (ft_strncmp(token.argv[0], "export", ft_strlen(token.argv[0])) == 0)
		return (0);
	else if (ft_strncmp(token.argv[0], "exit", ft_strlen(token.argv[0])) == 0)
		return (0);
	return (1);
}

static void	ms_exe_loop_sub(t_data *data, int *fd)
{
	if (fd[1] != STDOUT_FILENO)
		sclose(fd[1]);
	data->file_in = NONE;
	data->file_out = NONE;
	data->typein = NONE;
	data->typeout = NONE;
}

static void	ms_exe_loop(t_token *token, t_token *last_token, int *fd, int fd_in)
{
	t_data	*data;

	data = get_pdata(NULL);
	while (token->type != NONE)
	{
		data->l_status = 0;
		if (token->l_status == 0)
			ms_fds(token, last_token, fd);
		if (token->type == CMD && (token[1].type == BUIL
				&& ms_check_built_nspipe(token[1]) == 0))
		{
			write(1, "\n", 1);
			break ;
		}
		if ((token->l_status == 0 || token[1].type != NONE)
			&& (data->file_out != -1 && data->file_in != -1))
			ms_commander(token, fd, fd_in, last_token);
		else
			ms_exe_loop_sub(data, fd);
		data->l_status = token->l_status;
		last_token = token;
		token++;
		fd_in = fd[0];
	}
}

void	ms_main_exe(t_token *token, t_data *data, int i)
{
	t_token	*last_token;
	t_token	*first_token;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	while (token[++i].type != NONE)
		if (token[i].l_status != 0)
			return ;
	last_token = smalloc(sizeof(t_token));
	if (!last_token)
	{
		throw_error("ERROR: smalloc at ms_main_exe failed.", NULL, NULL);
		return ;
	}
	last_token->type = NONE;
	first_token = token;
	data->typein = NONE;
	data->typeout = NONE;
	if (token->type == NONE)
		data->l_status = token->l_status;
	ms_exe_loop(token, last_token, fd, STDIN_FILENO);
	ms_post_exe(data, last_token, first_token);
	token->l_status = 0;
}
