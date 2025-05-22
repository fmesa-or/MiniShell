/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:06:25 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 23:57:39 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char *av, t_token *tk, t_list *env, t_data *data)
{
	char	**path;
	char	*aux;
	t_list	*key;
	int		i;

	i = 0;
	key = find_key(env, "PATH");
	if (!key || ft_strchr(av, '/') != -1)
	{
		tk->command = ft_strdup(av, data);
		tk->type = CMD;
		return (1);
	}
	path = ft_split(key->value, ':', data);//segfault cuando unset PATH
	if (!path)
		throw_error("ERROR: PATH not found (2)", tk, data);
	while (path[i])
	{
		aux = ft_strcjoin(path[i], av, '/', data);
		if (access(aux, X_OK) == 0)
		{
			tk->command = ft_strdup(aux, data);
			tk->type = CMD;
//			free_2ptr(path, data);
//			sfree(aux, data);
			return (1);
		}
		i++;
	}
//	free_2ptr(path, data);
	//if (aux)
//	sfree(aux, data);
	return (0);
}

/*******************************************************
*If is BUILTIN stores it in token->command and return 1*
*******************************************************/
int	is_builtin(t_token *tk, char *av, t_data *data)
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
			tk->command = ft_strdup(aux[i], data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_av(t_list **lst, char *str, int j, t_token *tk, t_data *data)
{
	int start;
	char *av;

	start = j;
	av = NULL;

	if (str[j] == '\'' || str[j] == '\"')
	{
		j = end_quote(str, j + 1, str[j], tk);
		if (j == -1)
			return (-1);
		av = ft_substr(str, start, j + 1 - start, data);
		if (ft_strlen(av) == 2) // si hay comillas vacias pasa de ese argv
			return (j + 1);
		ft_lstadd_back(lst, ft_lstnew(av, "q", data)); //le dejo una q en el value para marcar quoted
		return(j + 1);//aqui devuelve con comillas
	}
	else
	{
		while (!ft_isspace(str[j]) && str[j])
			j++;
		av = ft_substr(str, start, j - start, data);
		ft_lstadd_back(lst, ft_lstnew(av, NULL, data));
		return (j);
	}
}
