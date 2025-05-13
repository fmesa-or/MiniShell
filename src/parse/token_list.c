/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/13 14:09:06 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tk_init(t_token *new)
{
	new->type = PIPE;
	new->command = NULL;
	new->redir = NULL;
	new->argv = NULL;
	new->av_list = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
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
		}
		else if (is_cmd(tk_list->argv[i], tk_list, env, data) == 1)
			flag++;
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
	{
		write(1, pipes[i], ft_strlen(pipes[i]));
		write(1, "\n", 1);
		i++;
	}
	tk_list = malloc(sizeof(t_token) * (i + 1));
	if (!tk_list)
	{
		throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, NULL);//pasarle data y token si necesario
		exit(errno);
	}
	i = 0;
	while (pipes[i])
	{
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
		if (tk_argvtipe(&tk_list[i], env, data) != 1)
		{
			throw_error("ERROR: in pipe cmd != 1", tk_list, NULL);
			return(NULL);
		}
		i++;
	}
	tk_list[i].type = NONE;
	return (tk_list);
}

//print_tokenlist(tk_list);
