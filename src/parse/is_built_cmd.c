/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:57:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/27 19:05:06 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmd_access_lloop(char *av, char *path, int i, t_token *tk)
{
	char	*aux;

	aux = ft_strcjoin(path[i], av, '/');
	if (access(aux, X_OK) == 0)
	{
		tk->command = ft_strdup(aux);
		tk->type = CMD;
		free_2ptr(path);
		sfree(aux);
		return (1);
	}
	return (0);
}

/*********************************************************
*If is a COMMAND stores it in token->command and return 1*
*********************************************************/
int	is_cmd(char *av, t_token *tk, t_list *env, t_data *data)
{
	char	**path;

	t_list	*key;
	int		i;

	i = 0;
	key = find_key(env, "PATH");
	if (!key || ft_strchr(av, '/') != -1)
	{
		tk->command = ft_strdup(av);
		tk->type = CMD;
		return (1);
	}
	path = ft_split(key->value, ':');//segfault cuando unset PATH
	if (!path)
		throw_error("ERROR: PATH not found (2)", tk, data);
	while (path[i])
	{
		if (ms_cmd_access_loop(av, path, i, tk) == 1)
			return (1);
		i++;
	}
	free_2ptr(path);
	return (0);
}

/*********************************************************
*If is a BUILTIN stores it in token->command and return 1*
*********************************************************/
int	is_builtin(t_token *tk, char *av)
{
	char	*aux[8];
	int		i;

	i = 0;
	aux[0] = "export\0";
	aux[1] = "unset\0";
	aux[2] = "cd\0";
	aux[3] = "pwd\0";
	aux[4] = "env\0";
	aux[5] = "exit\0";
	aux[6] = "echo\0";
	aux[7] = 0;
	while (aux[i])
	{
		if (ft_strcmp(av, aux[i]) == 0)
		{
			tk->type = BUIL;
			tk->command = ft_strdup(aux[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
