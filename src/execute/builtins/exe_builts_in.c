/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/03/11 12:49:57 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builts(t_token *token, t_data *data)
{
	int	ret;

		printf("ms_builts access\n");
	dup2(token->fd[1], 1);
	dup2(token->fd[0], 0);
	ret = 0;
	if (ft_strncmp(token->argv[0], "cd", ft_strlen(token->argv[0])) == 0)
		ret = bi_change_dir(token, data);
	if (ft_strncmp(token->argv[0], "pwd", ft_strlen(token->argv[0])) == 0)
		ret = bi_print_working_directory(data);
	if (ft_strncmp(token->argv[0], "echo", ft_strlen(token->argv[0])) == 0)
			ret = bi_echo(token);
	if (ft_strncmp(token->argv[0], "export", ft_strlen(token->argv[0])) == 0)
		ret = bi_export(data->exported_list, token->argv[1]);
//	if (ft_strncmp(token->argv[0], "unset", ft_strlen(token->argv[0])) == 0)
//		ret = bi_unset();
	if (ft_strncmp(token->argv[0], "env", ft_strlen(token->argv[0])) == 0)
		ret = bi_env(data, token);
	if (ft_strncmp(token->argv[0], "exit", ft_strlen(token->argv[0])) == 0)
		ret = bi_exit(token->argv);


	return (ret);
}
