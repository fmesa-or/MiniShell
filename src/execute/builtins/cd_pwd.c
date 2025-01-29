/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:11:13 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 13:42:35 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int bi_cd2(t_token *token, t_data *data, char *target_path, int cd_stat)
{
	target_path = token->argv[1];
	ft_export (data->exported_list, ft_strcjoin("OLDPWD", getcwd(NULL, 0), '='));
	cd_stat = chdir(target_path);
	if (cd_stat != 0)
		throw_error("ERROR: no find rute", NULL, data);
	else
	{
		free(data->pwd);
		ft_export (data->exported_list, ft_strcjoin("PWD", getcwd(NULL, 0), '='));
		data->pwd = getcwd(NULL, 0);
		if (!data->pwd)
			throw_error("ERROR: failed to update pwd", NULL, data);
	}
	return (cd_stat);
}


int	bi_change_dir(t_token *token, t_data *data)
{
	char	*target_path;
	int		cd_stat;

	cd_stat = 0;
	if (token->argv[2])
		throw_error("ERROR:", NULL, data);//REVISAR FUNCION
	else
	{
		if (!(token->argv[1]) || ft_strncmp(token->argv[1], "$HOME", 5) == 0 || ft_strncmp(token->argv[1], "~", 1) == 0)
		{
			target_path = getenv("HOME");
			if (!target_path)
				throw_error("ERROR:", NULL, data);
		}
		else
			cd_stat = bi_cd2(token, &data, target_path, cd_stat);
	}
	return (cd_stat);
}

int	bi_print_working_directory(t_data *data)
{
	if (data->pwd != NULL)
		write(1, data->pwd, ft_strlen(data->pwd));
	else
	{
		data->pwd = getcwd(NULL, 0);
		if (data->pwd != NULL)
			write(1, data->pwd, ft_strlen(data->pwd));
		else
			perror("pwd");
	}
	return (0);
}
