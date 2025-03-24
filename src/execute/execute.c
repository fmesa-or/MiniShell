/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:35:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/03/24 11:31:50 by fmesa-or         ###   ########.fr       */
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

void	ms_fds(t_token *token, t_token **token_prev, t_data *data)
{
//	printf("next token type = %d\n", token[1].type);
//	printf("actual token type = %d\n", token->type);
	if (token[1].type != NONE)
		ms_pipe(token);
//	printf("PIPE PASSED");
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
//	printf(RD"Token.Type = %d\n"RES, token->type);
	if (token->type == BUIL && token[1].command == NULL)//hay que arreglarlo para que sea con todo el token
	{
		token->l_status = ms_builts(token, data);
		printf(GR"BUIL CHECK\n"RES);
	}
	else
	{
		token->pid = fork();
		if (token->pid == 0)
		{
			if (token->type == BUIL)
			{
//				printf(FF"CHECK BUIL"RES);
				ms_builts(token, data);
				exit(0);
			}
			else
			{
//				printf(CI"CHECK CHILDS\n"RES);
				ms_exe_childs(token, data);
			}
		}
		else
		{
//			printf(PR"CHECK CLOSE\n"RES);
			if (token->fd[0] != 0)
				close(token->fd[0]);
			if (token->fd[1] != 1)
				close(token->fd[1]);
		}
	}
}

void	ms_main_exe(t_token *token, t_data *data)
{
	t_token	*token_prev;
	t_token *token_post;
//	static int j = 0;

	token_post = token;
	while(token->type != NONE)
	{
//		printf("entrada bucle\n");
		ms_fds(token, &token_prev, data);
//		printf("señal procesada en ms_fds\n");
		ms_commander(token, data);
//		printf("señal procesada en ms_commander\n");
		token_prev = token;
		token++;
//		printf("fin bucle: %d\n", ++j);
	}
	ms_post_exe(data, token_prev, token_post);
}