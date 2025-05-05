/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/05 12:13:18 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	ms_fds(t_token *token, t_token *token_prev, t_data *data, int *fd)
{
	if (token->redir)
	{
		token->l_status = ms_init_redir(token, data, fd, token_prev);
//		if (token->l_status == 1)//revisar, creo que o no es necesario, o no aplica así
//		{
//			token_prev = token;
//			close(fd[0]);
//			close(fd[1]);
//			close(token->fd[0]);// lo mismo si, lo mismo no
//			return ;
//		}
	}
	if (token[1].type != NONE)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
//		dprintf(2, PR"PIPE\n"RES);
	}
//	if (token_prev->type != NONE)
//	{
//		dup2(fd[0], 0);
//		close(fd[0]);
//		close(fd[1]);
//	}
//	dprintf(2, RD"CHECK FDS: [0]: %d y [1]: %d\n"RES, fd[0], fd[1]);
	if (token_prev->type == NONE)//borrar
		token_prev->type = NONE;//borrar
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
	return(1);
}

void ms_commander(t_token *token, t_data *data, int fd[2], int fd_in, t_token *token_prev)
{
	int	status;

	if (token->type != CMD && token->type != BUIL)
		return;
	if (token->type == BUIL && (token[1].type == NONE && token_prev->type == NONE))
	{
		token->l_status = ms_builts(token, data, token_prev);
		printf("BUIL CHECK\n");
	}
	else
	{
		token->pid = fork();
		if (token->pid == 0) //if es el hijo
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
//				printf("CHECK CHILDS: %s REDIR: fd[0]:%d fd[1]:%d\n"RES, token->command, token->fd[0], token->fd[1]);
				ms_exe_childs(token, data, fd, fd_in);
			}
		}
		else //es el padre
		{
			waitpid(token->pid, &status, 0);
			dprintf(2, "Check PADRE: %s fd[0]:%d fd[1]:%d\n", token->command, token->fd[0], token->fd[1]);
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
	int fd[2];//Los fd que vamos a usar para la pipe
	int	fd_in;//Almacenamos el SDTIN en un entero.

	last_token = malloc(sizeof(t_token));
	fd_in = STDIN_FILENO;
	if (!last_token)
		throw_error("ERROR: malloc didn't work as expected.", NULL, data);
	last_token->type = NONE;
	first_token = token;
	data->typein = NONE;
	data->typeout = NONE;
	while(token->type != NONE)
	{
		ms_fds(token, last_token, data, fd);
		if (token->type == CMD && (token[1].type == BUIL && ms_check_built_npipe(token[1]) == 0))
		{
			write(1, "\n", 1);
			break ;
		}
		ms_commander(token, data, fd, fd_in, last_token);
		last_token = token;
		token++;
		fd_in = fd[0];
//		write(2, "Check while!!\n", 15);
	}
	ms_post_exe(data, last_token, first_token);
}
