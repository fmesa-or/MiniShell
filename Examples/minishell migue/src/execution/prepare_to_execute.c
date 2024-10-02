/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumar2 <migumar2@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:13:57 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/17 13:46:59 by migumar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static void	kill_children(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->pid > 0)
			kill(tokens->pid, SIGKILL);
		tokens = tokens->prev;
	}
}

void	post_execution(t_all *data, t_token *last_token)
{
	g_sig = 2;
	signal_handler();
	waitpid(last_token->pid, &(last_token->last_status), 0);
	data->last_status = last_token->last_status;
	if (WIFEXITED(last_token->last_status))
		last_token->last_status = WEXITSTATUS(last_token->last_status);
	data->last_status = last_token->last_status;
	kill_children(last_token->prev);
	dup2(data->bk_in, STDIN_FILENO);
	dup2(data->bk_out, STDOUT_FILENO);
}

void	process_token_fds(t_token *l_token, t_token **last_token)
{
	if (l_token->next && (l_token->next)->type == PIPE)
		create_pipe(l_token->next);
	if (l_token->redir)
	{
		l_token->last_status = init_redir(l_token);
		if (l_token->last_status == 1)
		{
			*last_token = l_token;
			close((*last_token)->fd[0]);
			close((*last_token)->fd[1]);
			return ;
		}
	}
	if (l_token->type == PIPE)
		return ;
}

void	process_token_cmd(t_all *data, t_token *l_token)
{
	if (l_token->type != CMD && l_token->type != BUIL)
		return ;
	if (l_token->type == BUIL && !l_token->next)
		l_token->last_status = run_builtin(data, l_token);
	else
	{
		l_token->pid = fork();
		if (l_token->pid == 0)
		{
			if (l_token->type == BUIL)
			{
				run_builtin(data, l_token);
				exit(0);
			}
			else
				execute_child(data, l_token);
		}
		else
		{
			if (l_token->fd[0] != 0)
				close(l_token->fd[0]);
			if (l_token->fd[1] != 1)
				close(l_token->fd[1]);
		}
	}
}

void	prepare_to_execute(t_all *data, t_token *l_token)
{
	t_token	*last_token;

	while (l_token)
	{
		process_token_fds(l_token, &last_token);
		process_token_cmd(data, l_token);
		last_token = l_token;
		l_token = l_token->next;
	}
	post_execution(data, last_token);
}
