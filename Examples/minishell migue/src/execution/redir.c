/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:25:01 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/17 14:06:15 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_redir(t_token *l_token, t_redir *redir)
{
	if ((!access(redir->file, F_OK) && access(redir->file, R_OK)
			&& redir->type == LT)
		|| (!access(redir->file, F_OK) && access(redir->file, W_OK)
			&& (redir->type == GT || redir->type == GGT)))
	{
		write(2, "minishell: ", 11);
		write(2, redir->file, ft_strlen(redir->file));
		write(2, ": Permission denied\n", 21);
		return (1);
	}
	else if (((l_token->fd[0] < 0 && (redir->type == LT || redir->type == LLT)))
		|| (l_token->fd[1] < 0 && (redir->type == GT || redir->type == GGT)))
	{
		write(2, "minishell: ", 11);
		write(2, redir->file, ft_strlen(redir->file));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}

static int	create_redir(t_token *l_token, t_redir *redir )
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	if (redir->type == GT)
		l_token->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == GGT)
		l_token->fd[1] = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == LT)
		l_token->fd[0] = open(redir->file, O_RDONLY);
	else if (redir->type == LLT)
		l_token->fd[0] = create_heredoc(redir->file);
	ret = error_redir(l_token, redir);
	if (redir->next && !ret)
	{
		if (create_redir(l_token, redir->next))
			ret = 1;
	}
	return (ret);
}

int	init_redir(t_token *l_token)
{
	t_redir	*redir;

	if (!l_token->redir)
		return (0);
	if (l_token->type == BUIL || l_token->type == CMD)
	{
		redir = l_token->redir;
		return (create_redir(l_token, redir));
	}
	return (0);
}
