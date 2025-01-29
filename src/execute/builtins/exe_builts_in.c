/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/29 12:58:16 by fmesa-or         ###   ########.fr       */
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


void	r_builts()
{}

/*
void	ft_builtin(t_token token, t_data data)
{
	//----Solo funcionan en minúsculas
	if (token.argv[0] == "cd")
		bi_change_dir(token, &data);
	//export
	//unset
	//exit

	//----Solo en mayus
	//----Ambos
	//echo & echo -n
	else if (ms_tolower_str(token.argv[0]) == "env")//vas por aquí
		bi_env();//preguntar a Ramón donde la almacenamos o si puedo usar getenv
	//pwd
	else if (ms_tolower_str(token.argv[0]) == "pwd")
		bi_print_working_directory(data);
}
*/
