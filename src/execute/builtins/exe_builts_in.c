/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 19:14:15 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	r_builts(t_token *token, t_data *data)
{
	int	ret;

	dup2(token->fd[1], 1);
	dup2(token->fd[0], 0);
	ret = 0;
	if (ft_strncmp(token->argv[0], "cd", ft_strlen(token->argv[0])) == 0)
		ret = bi_change_dir(token, data);
	if (ft_strncmp(token->argv[0], "pwd", ft_strlen(token->argv[0])) == 0)
		ret = bi_print_working_directory(data);
		//MORE

	return (ret);
}
