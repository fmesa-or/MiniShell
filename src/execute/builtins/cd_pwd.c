/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:11:13 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/21 17:41:21 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************
*If token->argv[1] is empty or has '~' in it returns 1.*
*******************************************************/
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
	char	*aux_pwd;

	cd_stat = (chdir(target_path) * -1);
	if (cd_stat != 0)
	{
		//check if access not granted
		if (access(target_path, X_OK))
			throw_error("ERROR: Permission denied", NULL, NULL);
		else
			throw_error("ERROR: No such file directory", NULL, NULL);
	}
	else
	{
//		free(data->pwd);
		dprintf(2, RD"CHECK: %s\n"RES, data->pwd);
		aux_pwd = getcwd(NULL, 0);
		data->pwd = aux_pwd;
		dprintf(2, RD"CHECK: %s\n"RES, data->pwd);
//		free(aux_pwd);
		if (!data->pwd)
			throw_error("ERROR: failed to update pwd", NULL, NULL);
	}
	return (cd_stat);
}

static int	bi_change_dir_sub(t_token *tk, t_data *data, char *target_path)
{
	int	cd_stat;

	cd_stat = 0;
	if (tk->argv[1] && ft_strcmp(tk->argv[1], "-") == 0)
	{
		target_path = data->oldpwd;
		cd_stat = bi_cd2(data, target_path, cd_stat);
		bi_print_working_directory(data);
	}
	else if (bi_cd_homer(tk) == 1)
	{
		target_path = getenv("HOME");
		if (target_path == NULL)
			throw_error("ERROR: HOME not set.", NULL, NULL);
		else
			cd_stat = bi_cd2(data, target_path, cd_stat);
	}
	else
	{
		target_path = tk->argv[1];
		cd_stat = bi_cd2(data, target_path, cd_stat);
	}
	return (cd_stat);
}

int	bi_change_dir(t_token *token, t_data *data)
{
	int		cd_stat;
	t_list	*aux;
	char	*aux_pwd;

	aux_pwd = NULL;
	cd_stat = 0;
	if (token->argv[1] && token->argv[2])
		throw_error("ERROR: cd: too many arguments.", NULL, NULL);
	else
	{
		aux_pwd = getcwd(NULL, 0);
		cd_stat = bi_change_dir_sub(token, data, NULL);
	}
//	free(data->oldpwd);
	data->oldpwd = aux_pwd;
//	free(aux_pwd);
	aux = find_key(data->exported_list, "PWD");
	if (!aux)
	{
//		ft_lstadd_back(&data->exported_list, ft_lstnew("PWD", data->pwd));
		export_var(data->exported_list, (ft_strjoin("PWD=", data->pwd)));
	}
	else
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
	if (!aux)
//		ft_lstadd_back(&data->exported_list, ft_lstnew("PWD", data->pwd));
		export_var(data->exported_list, (ft_strjoin("PWD=", data->pwd)));
	else
		aux->value = data->pwd;
	return (0);
}
