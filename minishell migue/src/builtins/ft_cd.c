/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:03:17 by migumar2          #+#    #+#             */
/*   Updated: 2024/07/15 18:28:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(t_all *data, char *dir)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, sizeof(char *));
	if (chdir(dir) < 0)
		return (com_error(data, "cd", dir, "No such file or directory"));
	edit_element_to_list_export(data, ft_strdup("PWD"),
		getcwd(NULL, sizeof(char *)));
	add_element_to_list_export(data, ft_strdup("OLDPWD"),
		ft_strdup(old_pwd));
	return (0);
}

int	cd_no_args(t_all *data, t_token *l_token)
{
	char	*home;
	int		result;

	home = find_var(data->exported_list, "HOME");
	if (!home)
		return (com_error(data, l_token->argv[0], NULL, "HOME not set"));
	else
	{
		result = change_dir(data, home);
		free (home);
		return (result);
	}
}

int	ft_cd(t_all *data, t_token *l_token)
{
	if (l_token->argc > 2)
		return (com_error(data, l_token->argv[0], NULL, "too many arguments"));
	else if (l_token->argc == 1)
		return (cd_no_args(data, l_token));
	else if (l_token->argv[1])
		return (change_dir(data, l_token->argv[1]));
	return (0);
}
