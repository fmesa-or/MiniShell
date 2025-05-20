/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 16:57:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	ms_fds(t_token *token, t_token *token_prev, t_data *data, int *fd)
{
	if (token[1].type != NONE)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	if (token->redir)
		token->l_status = ms_init_redir(token, data, fd, token_prev);
}

static int	ms_check_built_npipe(t_token token)
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
		token->l_status = ms_builts(token, data, token_prev);
	else
	{
		token->pid = fork();
		if (token->pid == 0)
		{
			if (token->type == BUIL)
			{
				if (data->typein == IN)
					dup2(data->file_in, STDIN_FILENO);
				else if (fd_in != STDIN_FILENO)
					dup2(fd_in, STDIN_FILENO);
				if (data->typeout == DOUT || data->typeout == NDOUT)
					dup2(data->file_out, STDOUT_FILENO);
				else if (token[1].type == CMD)
					dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				ms_builts(token, data, token_prev);
				exit(0);
			}
			else
			{
				ms_exe_childs(token, data, fd, fd_in);
			}
		}
		else
		{
			waitpid(token->pid, &status, 0);
			if (fd[1] != STDOUT_FILENO)
				close(fd[1]);
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

	last_token = malloc(sizeof(t_token));
	fd_in = STDIN_FILENO;
	if (!last_token)
	{
		throw_error("ERROR: malloc didn't work as expected.", NULL, data);
		exit(errno);
	}
	last_token->type = NONE;
	first_token = token;
	data->typein = NONE;
	data->typeout = NONE;
	while (token->type != NONE)
	{
		token->l_status = 0;
		ms_fds(token, last_token, data, fd);
		if (token->type == CMD && (token[1].type == BUIL
				&& ms_check_built_npipe(token[1]) == 0))
		{
			write(1, "\n", 1);
			break ;
		}
		if (token->l_status == 0 || token[1].type != NONE)
			ms_commander(token, data, fd, fd_in, last_token);
		last_token = token;
		token++;
		fd_in = fd[0];
	}
	ms_post_exe(data, last_token, first_token);
}
