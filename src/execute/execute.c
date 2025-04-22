/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/20 21:00:41 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************************
*1st:	Set the pipe.                          *
*2nd:	Sets the child process and executes it.*
***********************************************/
/*void	child_process(t_token *token)
{
	if (pipe(token->fd) == -1)
				throw_error("ERROR: fork didn't work as expected.", token, data);

	token->pid = fork();
	if (token->pid == -1)
		throw_error("ERROR: fork didn't work as expected.", token, data);
	else if (token->pid == 0)
	{
		close(token->fd[0]);
		dup2(token->fd[1], STDOUT_FILENO);
		ft_execute(token->type, token->env);
	}
	else
	{
		close(token->fd[1]);
		dup2(token->fd[0], STDIN_FILENO);
	}
}*/

void	ms_fds(t_token *token, t_token *token_prev, t_data *data)
{
	if (token[1].type != NONE)
	{
		if (pipe(token->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		dprintf(2, PR"PIPE\n"RES);
	}
	if (token_prev->type != NONE)
	{
		dup2(token_prev->fd[0], 0);
		close(token_prev->fd[0]);
		close(token_prev->fd[1]);
	}
	if (token->redir)
	{
		token->l_status = ms_init_redir(token, data);
		if (token->l_status == 1)//revisar, creo que o no es necesario, o no aplica así
		{
			token_prev = token;
			close(token_prev->fd[0]);
			close(token_prev->fd[1]);
			close(token->fd[0]);// lo mismo si, lo mismo no
			return ;
		}
	}
	dprintf(2, RD"CHECK FDS: [0]: %d y [1]: %d\n"RES, token->fd[0], token->fd[1]);
}


void ms_commander(t_token *token, t_data *data)
{
	if (token->type != CMD && token->type != BUIL)
		return;

	if (token->type == BUIL && token[1].type == NONE)
	{
		token->l_status = ms_builts(token, data);
		printf("BUIL CHECK\n");
	}
	else
	{
		token->pid = fork();
		if (token->pid == 0) //if es el hijo
		{
			if (token->type == BUIL)
			{
				ms_builts(token, data);
				exit(0);
			}
			else
			{
				printf("CHECK CHILDS: %s REDIR: fd[0]:%d fd[1]:%d\n"RES, token->command, token->fd[0], token->fd[1]);
				ms_exe_childs(token, data);
			}
		}
		else //es el padre
		{
			dprintf(2, "Check PADRE: %s fd[0]:%d fd[1]:%d\n", token->command, token->fd[0], token->fd[1]);
			if (token->fd[1] != STDOUT_FILENO)
				close(token->fd[1]);
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

	last_token = malloc(sizeof(t_token));
	if (!last_token)
		throw_error("ERROR: malloc didn't work as expected.", NULL, data);
	last_token->type = NONE;
	first_token = token;
	while(token->type != NONE)
	{
		ms_fds(token, last_token, data);
		ms_commander(token, data);
		last_token = token;
		token++;
		write(2, "Check while!!\n", 15);
	}
	ms_post_exe(data, last_token, first_token);
}