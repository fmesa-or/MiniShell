/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:14:09 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/29 16:47:41 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static void	ms_com_sub(t_data *data, t_token *token, t_token *token_prev)
{
	if (data->typein == IN)
		sdup2(data->file_in, STDIN_FILENO);
	if (data->typeout == DOUT || data->typeout == NDOUT)
		sdup2(data->file_out, STDOUT_FILENO);
	token->l_status = ms_builts(token, data, token_prev);
}

static void	ms_father(t_data *data, t_token *tk_prev, t_token *token, int *fd)
{
	int		status;

	status = 0;
	waitpid(token->pid, &status, 0);
	data->l_status = tk_prev->l_status;
	if (WIFEXITED(status))
		token->l_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		tk_prev->l_status = 128 + WTERMSIG(status);
	data->l_status = token->l_status;
	if (fd[1] != STDOUT_FILENO)
		sclose(fd[1]);
	data->file_in = NONE;
	data->file_out = NONE;
	data->typein = NONE;
	data->typeout = NONE;
}

static void	ms_buil_child(int fd_in, t_token *token, int *fd, t_token *tk_prev)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (data->typein == IN)
		sdup2(data->file_in, STDIN_FILENO);
	else if (fd_in != STDIN_FILENO)
		sdup2(fd_in, STDIN_FILENO);
	if (data->typeout == DOUT || data->typeout == NDOUT)
		sdup2(data->file_out, STDOUT_FILENO);
	else if (token[1].type == CMD)
		sdup2(fd[1], STDOUT_FILENO);
	sclose(fd[0]);
	sclose(fd[1]);
	ms_builts(token, data, tk_prev);
	sexit(0);
}

void	ms_commander(t_token *token, int fd[2], int fd_in, t_token *token_prev)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (token->type != CMD && token->type != BUIL)
		return ;
	if (token->type == BUIL && (token[1].type == NONE
			&& token_prev->type == NONE))
	{
		ms_com_sub(data, token, token_prev);
	}
	else
	{
		token->pid = fork();
		if (token->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (token->type == BUIL)
				ms_buil_child(fd_in, token, fd, token_prev);
			else
				ms_exe_childs(token, data, fd, fd_in);
		}
		else
			ms_father(data, token_prev, token, fd);
	}
}
