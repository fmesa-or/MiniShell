/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:29:13 by jholland          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **argv)
{
	if (!*argv)
		return (0);
	if (same_string(argv[0], "cd") || same_string(argv[0], "pwd")
		|| same_string(argv[0], "env") || same_string(argv[0], "exit")
		|| same_string(argv[0], "echo") || same_string(argv[0], "unset")
		|| same_string(argv[0], "export"))
		return (1);
	return (0);
}

int	run_builtin(t_all *data, t_token *l_token)
{
	int	result;

	dup2(l_token->fd[1], 1);
	dup2(l_token->fd[0], 0);
	result = 0;
	if (same_string(l_token->argv[0], "cd"))
		result = ft_cd(data, l_token);
	else if (same_string(l_token->argv[0], "pwd"))
		result = ft_pwd(data);
	else if (same_string(l_token->argv[0], "env"))
		result = ft_env(data);
	else if (same_string(l_token->argv[0], "exit"))
		result = ft_exit(data, l_token->argv);
	else if (same_string(l_token->argv[0], "echo"))
		result = ft_echo(l_token->argv);
	else if (same_string(l_token->argv[0], "unset"))
		result = ft_unset(data, l_token->argv);
	else if (same_string(l_token->argv[0], "export"))
		result = ft_export(data, l_token->argv);
	return (result);
	close(l_token->fd[0]);
	close(l_token->fd[1]);
	return (result);
}
