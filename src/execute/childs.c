/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:17:17 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/22 00:04:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_check_permision(char *command, t_token *token)
{
	if (access(command, X_OK))
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": Command error\n", 16);
		(void) token;//borrar
		sexit(127);
	}
}


void	ms_exe_childs(t_token *token, t_data *data, int fd[2], int fd_in)
{
	int final[2];

	if (data->typein == IN)
		sdup2(data->file_in, STDIN_FILENO);
	else if (fd_in != STDIN_FILENO)
		sdup2(fd_in, STDIN_FILENO);
	if (data->typeout == DOUT || data->typeout == NDOUT)
		sdup2(data->file_out, STDOUT_FILENO);
	else if (token[1].type == CMD)
		sdup2(fd[1], STDOUT_FILENO);
	if (token->l_status != 0 && token[1].type != NONE)
		sexit(1);
	else
	{
		ms_check_permision(token->command, token);
		final[0] = dup(STDIN_FILENO);
		final[1] = dup(STDOUT_FILENO);
		sclose_all();
		dup2(final[0], STDIN_FILENO);
		dup2(final[1], STDOUT_FILENO);
		close(final[0]);
		close(final[1]);
		if (execve(token->command, token->argv, ms_return_env(data)) == -1)
			token->l_status = ms_cmd_nf(token->argv[0]);
	}
	sexit(127);
}
