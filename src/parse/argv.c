/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:32:35 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/26 17:34:11 by rmarin-j         ###   ########.fr       */
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
	path = ft_split(key->value, ':');
	if (!path)
		throw_error("ERROR: PATH not found (2)", tk, data);
	while (path[i])
	{
		aux = ft_strcjoin(path[i], av, '/');
		if (access(aux, X_OK) == 0)
		{
			tk->command = ft_strdup(aux);
			tk->type = CMD;
			free_2ptr(path);
			free(aux);
			return (1);
		}
		i++;
	}
	free_2ptr(path);
	if (aux)
		free(aux);
	return (0);
}

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

void	tk_argvtipe(t_token *tk_list, t_list *env, t_data *data)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = 0;
	while (tk_list->argv[i])
	{
		if (is_builtin(tk_list, tk_list->argv[i]) == 1)
		{
			if ((ft_strcmp(tk_list->argv[i], "cd") == 0) && (ft_strcmp(tk_list->argv[i + 1], "..") == 0))
 				i++;
			flag ++;
		}	
		else if (is_cmd(tk_list->argv[i], tk_list, env, data) == 1)
			flag++;
		i++;
	}
	if (flag == 0)
		throw_error("ERROR: no cmd in pipe\n", tk_list, data);
	else if (flag > 1)
		throw_error("ERROR: too much cmd in pipe\n", tk_list, data);
	tk_list->argc = i;
}

int get_av(t_list **lst, char *str, int j)
{
	int start;
	char *av;

	start = j;
	av = NULL;
	if (str[j] == '\'' || str[j] == '\"')
	{
		j = end_quote(str, j + 1, str[j]);
		av = ft_substr(str, start, j + 1 - start);
		if (ft_strlen(av) == 2) // si hay comillas vacias pasa de ese argv
			return (j + 1);
		ft_lstadd_back(lst, ft_lstnew(av, "q")); //le dejo una q en el value para marcar quoted
		return(j + 1);//aqui devuelve con comillas
	}
	else
	{
		while (!ft_isspace(str[j]) && str[j])
			j++;
		av = ft_substr(str, start, j - start);
		ft_lstadd_back(lst, ft_lstnew(av, NULL));
		return (j);
	}
}
