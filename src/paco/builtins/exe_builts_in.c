/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/02/19 15:19:38 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	bi_env()
{
	
}*/

void	bi_print_working_directory(t_data data)
{
	if (data.pwd != NULL)
		printf("%s\n", data.pwd);
	else
	{
		data.pwd = getcwd(NULL, 0);
		if (data.pwd != NULL)
			printf("%s\n", data.pwd);
		else
			perror("pwd");
	}
}

void	bi_change_dir(t_token token, t_data *data)
{
	char	*target_path;
	int		cd_stat;

	if (argv[2])
	{
		throw_error("ERROR:", NULL, data);
	}
	else
	{
		if (!token.argv[1] || strcmp(token.argv[1], "$HOME") == 0 || strcmp(token.argv[1], "~") == 0)
		{
			target_path = getenv("HOME");
			if (!target_path)
				throw_error("ERROR:", NULL, data);
		}
		else
		{
			target_path = token.argv[1];
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
					//ERROR
			}
		}
	}
}
int	ft_built_run(t_data *data, t_token *token)
{
	int	lstat;

	dup2(token->fd[1], 1);
	dup2(token->fd[0], 0);
	lstat = 0;
	if (ft_strcmp(token->argv[0], "cd"))
		lstat = ft_cd(token->argv, data);
	else if (ft_strcmp(token->argv[0], "pwd"))
		lstat = ft_pwd();
	else if (ft_strcmp(token->argv[0], "env"))
		lstat = ft_env(data->exported_list);
	else if (ft_strcmp(token->argv[0], "exit"))
		lstat = ft_exit(token->argv);
	else if (ft_strcmp(token->argv[0], "echo"))
		lstat = ft_echo(token->argv);
	else if (ft_strcmp(token->argv[0], "unset"))
		lstat = ft_unset(data->exported_list, token->argv[1]);
	else if (ft_strcmp(token->argv[0], "export"))
		lstat = ft_export(data->exported_list, token->argv[1]);
	close(token->fd[0]);
	close(token->fd[1]);
	return (lstat);
}
