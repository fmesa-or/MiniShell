/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/28 21:13:09 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tk_init(t_token *new)
{
	new->type = NONE;
	new->command = NULL;
	new->redir = NULL;
	new->argv = NULL;
	new->av_list = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->l_status = 0;
}

static int	tk_argvtipe(t_token *tk_list, t_list *env, t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (tk_list->argv[i])
	{
		if (is_builtin(tk_list, tk_list->argv[i]) == 1)
		{
			if (((ft_strcmp(tk_list->argv[i], "cd") == 0) && (tk_list->argv[i + 1])) && (ft_strcmp(tk_list->argv[i + 1], "..") == 0))
				i++;
			flag ++;
			break ;
		}
		else if (is_cmd(tk_list->argv[i], tk_list, env, data) == 1)
		{
			flag++;
			break ;
		}
		i++;
	}
	tk_list->argc = i;
	return (flag);
}

t_token	*tk_list_make(char **pipes, t_list *env, t_data *data)
{
	int		i;
	int		j;
	t_token	*tk_list;
	
	i = 0;
	j = 0;
	while (pipes[i])
		i++;
	tk_list = smalloc(sizeof(t_token) * (i + 1));
	if (!tk_list)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		sexit(errno);
	}
	i = 0;
	while (pipes[i])
	{
		/*
		Si el input es | // "" // '' // | cmd --> tenemos un segfault
		nota: arreglando el problema de las comillas, debería solucionarse con
			en get_av segurmanente.
		Si el input es cmd | --> se está ejecutando y no debería. 
		nota: Seguramente habrá que checkearlo antes de incluso llegar aquí!!
		*/
		if (pipes[i][0] == 0)//es solo una tirita para e problema de "|" y "| cmd", pero hace falta algo para "cmd |"
			break ;
		tk_init(&tk_list[i]);
		j = 0;
		while (pipes[i][j]) //en este buble inspeccionamos la linea de cada pipe char x char
		{
			while (ft_isspace(pipes[i][j]))
				j ++;				
			if (pipes[i][j] == '<' || pipes[i][j] == '>')
			{
				get_redir(&tk_list[i], pipes[i], j, data);
				pipes[i] = rd_strdel(ft_redirlast(tk_list[i].redir), pipes[i]); //añadir lo de las comillas
			}
			else if (pipes[i][j] && (pipes[i][j] != '<' && pipes[i][j] != '>' && !ft_isspace(pipes[i][j])))
				j = get_av(&tk_list[i].av_list, pipes[i], j, tk_list);//funcion q saca un arg, teniendo en cuenta q este primer char puede ser ' o ";
			if (j == -1)
				return(NULL);
		}
		tk_list[i].argv = listtoargv(tk_list[i].av_list);
		if (!tk_list->argv[0] && tk_list->redir->type == 4 && tk_list->redir->file)
		{
			ft_fake_hdoc(tk_list);
			ft_tokenclear(tk_list);
			tk_list->l_status = 42;
			return (tk_list);
		}
		else if (tk_argvtipe(&tk_list[i], env, data) < 1 && tk_list->l_status != 2)
		{
			throw_error("ERROR: command not found", NULL, NULL);
			tk_list[i].l_status = 127;
			tk_list->l_status = 127;
			return (tk_list);
		}
		i++;
	}
	tk_list[i].type = NONE;
	return (tk_list);
}
