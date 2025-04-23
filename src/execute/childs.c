/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:17:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/04/22 14:18:56 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*ms_find_path(char *argv, t_data *data)
{
	char			*try_path;
	char			*path;
	char			**dirs;
	unsigned int	i;

	path = ms_find_var

	return ();
}
*/

/*static int	ms_is_path(char *command)
{
	if (!command)
		return (0);
	if (command[0] == '.' && command[1] == '/')
		return (1);
	if (command[0] == '/')
		return (1);
	return (0);
}*/

void	ms_check_permision(char *command)
{
	if (access(command, X_OK))
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
}


void	ms_exe_childs(t_token *token, t_data *data, int fd[2], int fd_in)
{

	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (token[1].type == CMD)
		dup2(fd[1], STDOUT_FILENO);
	dprintf(2, "exe_childs command = %s\n", token->command);//checker
//	if (token->fd[0] != 0)
//		close(token->fd[0]);
//	if (token->fd[1] != 1)
//		close(token->fd[1]);
	close(fd[0]);
	close(fd[1]);
	dprintf(2, CI"STDIN: %d || STDOUT: %d\n", STDIN_FILENO, STDOUT_FILENO);
	dprintf(2, "EXECUTE CHILDS: %s REDIR: fd[0]:%d fd[1]:%d\n"RES, token->command, token->fd[0], token->fd[1]);
	if (execve(token->command, token->argv, ms_return_env(data)) == -1)
		ms_cmd_nf(token->argv[0]);
	exit(127);
}