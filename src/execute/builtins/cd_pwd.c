/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:11:13 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/20 14:55:16 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bi_cd_homer(t_token *token)
{
	if (!token->argv[1])
		return (1);
	if (ft_strcmp(token->argv[1], "~") == 0)
		return (1);
	return (0);
}

static int	bi_cd2(t_data *data, char *target_path, int cd_stat)
{
	cd_stat = chdir(target_path);
	if (cd_stat != 0)
		throw_error("ERROR: no find rute", NULL, data);
	else
	{
		free(data->pwd);
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
	t_list	*aux;
	char	*aux_pwd;

	aux_pwd = NULL;
	target_path = NULL;
	cd_stat = 0;
	if (token->argv[2])
		throw_error("ERROR:", NULL, data);
	else
	{
		aux_pwd = getcwd(NULL, 0);
		if (token->argv[1] && ft_strcmp(token->argv[1], "-") == 0)
		{
			bi_print_working_directory(data);
			target_path = data->oldpwd;
			cd_stat = bi_cd2(data, target_path, cd_stat);
		}
		else if (bi_cd_homer(token) == 1)
		{
			target_path = getenv("HOME");
			if (!target_path)
				throw_error("ERROR:", NULL, data);
			cd_stat = bi_cd2(data, target_path, cd_stat);
		}
		else
		{
			target_path = token->argv[1];
			cd_stat = bi_cd2(data, target_path, cd_stat);
		}
	}
	data->oldpwd = aux_pwd;
	aux = find_key(data->exported_list, "PWD");
	aux->value = data->pwd;
	return (cd_stat);
}

int	bi_print_working_directory(t_data *data)
{
	t_list	*aux;

	if (data->pwd != NULL)
	{
		write(1, data->pwd, ft_strlen(data->pwd));
		write(1, "\n", 1);
	}
	else
	{
		data->pwd = getcwd(NULL, 0);
		if (data->pwd != NULL)
		{
			write(1, data->pwd, ft_strlen(data->pwd));
			write(1, "\n", 1);
		}
		else
			perror("pwd");
	}
	aux = find_key(data->exported_list, "PWD");
	aux->value = data->pwd;
	return (0);
}
