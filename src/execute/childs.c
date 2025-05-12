/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:17:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/07 12:25:43 by fmesa-or         ###   ########.fr       */
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

void	ms_check_permision(char *command, t_token *token)
{
	if (access(command, X_OK))
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": Permission denied\n", 20);
		token->l_status = 126;//revisar si es necesario ponerlo aquí también, yo diría que no.
		exit(126);
	}
}


void	ms_exe_childs(t_token *token, t_data *data, int fd[2], int fd_in)
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
	if (token->l_status != 0 && token[1].type != NONE)
		exit(1);
	else
	{
		ms_check_permision(token->command, token);
		if (execve(token->command, token->argv, ms_return_env(data)) == -1)
			token->l_status = ms_cmd_nf(token->argv[0]);//dudas si neecsita devolver este valor.
	}
	exit(127);
}