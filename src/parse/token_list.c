/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/11/15 13:58:52 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tk_init(t_token *new)
{
	new->type = PIPE;
	new->command = NULL;
	new->redir = NULL;
	new->argv = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
}
int	is_cmd(char *av,t_token *tk, t_list *env)
{
	char	**path;
	char	*aux;
	t_list	*key;
	int	i;
	
	i = 0;
	key = find_key(env, "PATH");
	path = ft_split(key->value, ':');
	if (!path)
		throw_error("ERROR: PATH not found (2)");
	while (path[i])
	{
		aux = ft_strcjoin(path[i], av, '/');
		if (access(aux, X_OK) == 0)
		{
			tk->command = ft_strdup(aux);
			tk->type = CMD;
			free(aux);
			return(1);			
		}
		i++;
	}
	return (0);
}

int	is_builtin(t_token *tk, char *av)
{
	char *aux[8];
	int	i;
	
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
		if(!ft_strcmp(av,aux[i]))
		{
			tk->type = BUIL;
			tk->command = ft_strdup(aux[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	tk_get_arg(t_token *tk_list, char *pipe, t_list *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	tk_list->argv = ft_split(pipe, ' ');
	while (tk_list->argv[i])
	{
		if (flag == 0)
		{
			flag = is_cmd(tk_list->argv[i], tk_list, env);
			if (flag == 0)
				flag = is_builtin(tk_list, tk_list->argv[i]);
		}
		i++;
	}
	if (flag == 0)
		throw_error("ERROR: no cmd in pipe");
	tk_list->argc = i;
	
	
}


t_token	*tk_list_make(char **pipes, t_list *env)
{
	int	i;
	t_token	*tk_list;

	i = 0;
	while (pipes[i])
		i++;
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i  = 0;	
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		tk_inrd(&tk_list[i], pipes[i]);
		tk_outrd(&tk_list[i], pipes[i]);
		if (tk_list[i].redir->type)
		{
			pipes[i] = rd_strdel(&tk_list[i], pipes[i]);
			printf("str = %s\n", pipes[i]);
		}
		tk_get_arg(&tk_list[i], pipes[i], env);
		i++;
	}
	tk_list[i].type = NONE;
	return(tk_list);
}
/*para terminar de completar este apartado tengo q rellenar
la struct data, q quedan el argv, q basta con un split(' ');
esto va a dar a su vez el argc y hay q encontrar el cmd
con esto metemos el type y dependiendo si es built o cmd
le metemos el path en la variable cmd*/

