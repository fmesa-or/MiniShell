/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 10:25:42 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_writer(int *fd, char *line, char *limiter)
{
	int	i;

	i = 5;
	if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		write(1, "> ", 2);
	else if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS); //revisar
	write(fd[1], line, ft_strlen(line));
}


/***********************************************
*1st:	Set the pipe.                          *
*2nd:	Sets the child process and executes it.*
***********************************************/
void	child_process(t_token token)
{
	if (pipe(token->fd) == -1)
		//ERROR
	token->pid = fork();
	if (token->pid == -1)
		//ERROR
	if (pid == 0)
	{
		close(token->fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_execute(token->type, token->env);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
	}
}

/*************************************************************************
*1st:	Starts the pipe.                                                 *
*2nd:	Starts the child process.                                        *
*3rd:	Read from the STDIN with GNL until it finds the limiter.         *
*************************************************************************/
void	ft_here_doc(t_token *token, t_data *data)
{
	pid_t	reader;
	char	*line;

	if (pipe(token->fd) == -1)
		throw_error("Error: Pipe not working.", token, &data);
	reader = fork();
	if (reader == 0)
	{
		close(token->fd[0]);
		write(1, "> ", 2);
		while (ms_gnl(&line))
			ft_writer(token->fd, line, token->redir->file);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
}



void	ms_fds(t_token *token, t_token **token_prev, t_data *data)
{
	if (token[1].type != NONE)
		c_pipe(token[1], token_prev);
	if (token->redir)
	{
		token->l_status = ms_init_redir(token, data);
		if (token->l_status == 1)//revisar, creo que o no es necesario, o no aplica así
		{
			*token_prev = token;
			close((*token_prev)->fd[0]);
			close((*token_prev)->fd[1]);
			return ;
		}
	}
}

void	ms_commander(t_token *token, t_data *data)
{
	if (token->type != CMD && token->type != BUIL)
		return ;
	if (token->type == BUIL && token[1].type == NONE)
		token->l_status = /*run_builtin*/;
	else
	{
		token->pid = fork();
		if (token->pid == 0)
		{
			if (token->type == BUIL)
			{
				/*run_builtin(data, token)*/;
				exit(0);
			}
			else
				/*execute_child*/;
		}
		else
		{
			if (token->fd[0] != 0)
				close(token->fd[0]);
			if (token->fd[1] != 1)
				close(token->fd[1]);
		}
	}
}

void	ft_main_exe(t_token *token, t_data *data)
{
	t_token	*token_prev;

	while(token->type != NONE)
	{
		ms_fds(token, &token_prev, data);
		ms_commander(token, data);
		token_prev = token;
		token++;
	}
//una vez terminado hay que hacer la post ejecucuión
}