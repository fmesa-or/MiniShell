/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 19:25:02 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builts(t_token *token, t_data *data, t_token *token_prev)
{
	int	ret;

	ret = 0;
	if ((ft_strncmp(token->argv[0], "cd", ft_strlen(token->argv[0])) == 0)
		&& (token[1].type == NONE && token_prev->type == NONE))
		ret = bi_change_dir(token, data);
	else if (ft_strncmp(token->argv[0], "pwd", ft_strlen(token->argv[0])) == 0)
		ret = bi_print_working_directory(data);
	else if (ft_strncmp(token->argv[0], "echo", ft_strlen(token->argv[0])) == 0)
		ret = bi_echo(token);
	else if ((ft_strncmp(token->argv[0], "export", ft_strlen(token->argv[0]))
			== 0) && (token[1].type == NONE && token_prev->type == NONE))
		ret = bi_export(data->exported_list, token->argv);
	else if ((ft_strncmp(token->argv[0], "unset", ft_strlen(token->argv[0]))
			== 0) && (token[1].type == NONE && token_prev->type == NONE))
		ret = bi_unset(data->exported_list, token->argv);
	else if (ft_strncmp(token->argv[0], "env", ft_strlen(token->argv[0])) == 0)
		ret = bi_env(data, token);
	else if ((ft_strncmp(token->argv[0], "exit", ft_strlen(token->argv[0]))
			== 0) && (token[1].type == NONE && token_prev->type == NONE))
		ret = bi_exit(token->argv);
	else
		return (0);
	return (ret);
}
