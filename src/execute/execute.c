/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 12:17:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	ms_fds(t_token *token, t_token *token_prev, t_data *data, int *fd)
{
	if (token[1].type != NONE)
	{
		if (spipe(fd) == -1)
		{
			perror("pipe");
			sexit(EXIT_FAILURE, data);
		}
	}
	if (token->redir)
		token->l_status = ms_init_redir(token, data, fd, token_prev);
}

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

void	ms_commander(t_token *token, t_data *data, int fd[2], int fd_in, t_token *token_prev)
{
	int	status;

	if (token->type != CMD && token->type != BUIL)
		return ;
	if (token->type == BUIL && (token[1].type == NONE
			&& token_prev->type == NONE))
		token->l_status = ms_builts(token, data, token_prev, fd);
	else
	{
		token->pid = fork();
		if (token->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			if (token->type == BUIL)
			{
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
				ms_builts(token, data, token_prev, fd);
				sexit(0, data);
			}
			else
				ms_exe_childs(token, data, fd, fd_in);
		}
		else
		{
			waitpid(token->pid, &status, 0);
			data->l_status = token_prev->l_status;
			if (WIFEXITED(status))
				token_prev->l_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				token_prev->l_status = 128 + WTERMSIG(status);
			data->l_status = token_prev->l_status;
			if (fd[1] != STDOUT_FILENO)
				sclose(fd[1]);
			data->file_in = NONE;
			data->file_out = NONE;
			data->typein = NONE;
			data->typeout = NONE;
		}
	}
}


/*
*token_prev es el último token
*token_post es el primer token de todo el string
*/
void	ms_main_exe(t_token *token, t_data *data)
{
	t_token	*last_token;
	t_token	*first_token;
	int		fd[2];
	int		fd_in;

	fd[0] = -1;
	fd[1] = -1;
//	if (token->l_status != 0)
//		data->l_status = token->l_status;
	last_token = smalloc(sizeof(t_token), data);
	if (!last_token)
	{
		throw_error("ERROR: smalloc at ms_main_exe failed\n", NULL, NULL);
		return ;
	}
	fd_in = STDIN_FILENO;
	if (!last_token)
	{
		throw_error("ERROR: smalloc didn't work as expected.", NULL, data);
		sexit(errno, data);
	}
	last_token->type = NONE;
	first_token = token;
	data->typein = NONE;
	data->typeout = NONE;
	while (token->type != NONE)
	{
		ms_fds(token, last_token, data, fd);
		if (token->type == CMD && (token[1].type == BUIL
				&& ms_check_built_nspipe(token[1]) == 0))
		{
			write(1, "\n", 1);
			break ;
		}
		if ((token->l_status == 0 || token[1].type != NONE) && (data->file_out != -1 && data->file_in != -1))
			ms_commander(token, data, fd, fd_in, last_token);
		else
		{
			if (fd[1] != STDOUT_FILENO)
				sclose(fd[1]);
			data->file_in = NONE;
			data->file_out = NONE;
			data->typein = NONE;
			data->typeout = NONE;
			data->l_status = token->l_status;
		}
		last_token = token;
		token++;
		fd_in = fd[0];
	}
	ms_post_exe(data, last_token, first_token);
	token->l_status = 0;
}
