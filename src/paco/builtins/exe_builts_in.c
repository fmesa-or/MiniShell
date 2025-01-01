/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builts_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:52:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/01/01 20:03:43 by fmesa-or         ###   ########.fr       */
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
	if (!token.argv[1] || strcmp(token.argv[1], "$HOME") == 0 || strcmp(token.argv[1], "~") == 0)
	{
		target_path = getenv("HOME");
		if (!target_path)
			//ERROR
	}
//	ms_tolower_str(&token.argv[1]);

	else
		target_path = token.argv[1];
	if (chdir(target_path) != 0)
	{
		//ERROR
	}
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		//ERROR
}

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
	else if (token.argv[0] == "env")
		bi_env();
	//pwd
	else if (ms_tolower_str(token.argv[0]) == "pwd")
		bi_print_working_directory(data);
}
