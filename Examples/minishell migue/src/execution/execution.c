/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:09:44 by jholland          #+#    #+#             */
/*   Updated: 2024/07/17 14:05:59 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_path(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '.' && str[1] == '/')
		return (1);
	if (str[0] == '/')
		return (1);
	return (0);
}

void	check_permision(char *command)
{
	if (access(command, X_OK))
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
}

void	execute_child(t_all *data, t_token *l_token)
{
	dup2(l_token->fd[1], 1);
	dup2(l_token->fd[0], 0);
	if (l_token->fd[0] != 0)
		close(l_token->fd[0]);
	if (l_token->fd[1] != 1)
		close(l_token->fd[1]);
	if (!l_token->argv[0])
		exit(0);
	else if (is_path(l_token->argv[0]) && !access(l_token->argv[0], F_OK))
		l_token->command = ft_strdup(l_token->argv[0]);
	else
	{
		l_token->command = find_path(l_token->argv[0], data);
		if (!l_token->command)
		{
			com_not_found(data, l_token->argv);
			exit(127);
		}
	}
	check_permision(l_token->command);
	if (execve(l_token->command, l_token->argv, ft_return_env(data)) == -1)
		com_not_found(data, l_token->argv);
	exit(127);
}
