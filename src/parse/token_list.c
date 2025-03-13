/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/13 15:02:09 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tk_init(t_token *new)
{
	new->type = PIPE;
	new->command = NULL;
	new->redir = NULL;
	new->argv->key = NULL;
	new->argv->value = NULL;
	new->argv->next = NULL;
	new->argv = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
}

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
		if (!ft_strcmp(av, aux[i]))
		{
			tk->type = BUIL;
			tk->command = ft_strdup(aux[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

/* void	tk_get_arg(t_token *tk_list, char *pipe, t_list *env, t_data *data)
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
			flag = is_cmd(tk_list->argv[i], tk_list, env, data);
			if (flag == 0)
				flag = is_builtin(tk_list, tk_list->argv[i]);
		}
		i++;
	}
	if (flag == 0)
		throw_error("ERROR: no cmd in pipe", tk_list, data);
	tk_list->argc = i;
} */

/*--------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------*/

// static int	ft_lstsize(t_redir *lst)
// {
// 	t_redir	*node;
// 	int		count;

// 	count = 0;
// 	node = lst;
// 	//if (!node)
// 		//printf("\nno redir en lstsize\n");
// 	while (node)
// 	{
// 		count++;
// 		node = node->next;
// 	}
// 	return (count);
// }

t_redir	*ft_redirlast(t_redir *rd)
{
	t_redir	*node;

	node = rd;
	while (node)
	{
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (node);
}
void	printredir(t_redir *red, char *str)
{
	return ;
	if (!red)
		printf("la redir no existe\n");
	printf("\n---------------\n");
	printf("-----REDIR-----\n\n");
	printf("PIPE = [ %s ]\n", str);
	printf("rd--> tipo = %i,  file = %s\n", red->type, red->file);
	printf("---------------\n\n");
}

int	get_redir(t_token *tk, char *str, int j)
{
	int	rd_end;
	
	rd_end = 0;
	if (str[j] == '<' && str[j + 1] == '<')
		rd_end = redir_fill(tk, str, HDOC, j);
	else if (str[j] == '>' && str[j + 1] == '>')
		rd_end = redir_fill(tk, str, NDOUT, j);
	else if (str[j] == '<')
		rd_end = redir_fill(tk, str, IN, j);
	else if (str[j] == '>')
		rd_end = redir_fill(tk, str, DOUT, j);
	return(rd_end);
}


char *get_av(char *str, int j)
{
	int start;

	start = j;
	if (str[j] == '\"')
		j = end_quote(str, j, '\"');
	else if (str[j] == '\'')
		j = end_quote(str, j, '\'');
	else
	{
		while (!ft_isspace(str[j]) && str[j])
			j++;
	}
	return(ft_substr(str, start, j));
}

t_token	*tk_list_make(char **pipes, t_list *env, t_data *data)
{
	int		i;
	int		j;
	//int		ac_ind; //esto sera el indice de tk->argv
	char	*av;
	t_token	*tk_list;

	i = sizeof(env[3]);
	i = 0;
	j = data->l_status;
	j = 0;
	while (pipes[i])
		i++;
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i = 0;
	
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		//tk->ac = funcion q haya el argc y me genera array de argv
		//ac_ind = 0;  ya q se reinicia en cada tk
		while(pipes[i][j]) //en este buble inspeccionamos la linea de cada pipe char x char
		{
			while (ft_isspace(pipes[i][j]))
				j++;
			if (pipes[i][j] == '<' || pipes[i][j] == '>')
			{
				get_redir(&tk_list[i], pipes[i], j);
				pipes[i] = rd_strdel(ft_redirlast(tk_list[i].redir), pipes[i]); //añadir lo de las comillas
				/* printf("Cantidad actual nodos redir = [%i]\n", ft_lstsize(tk_list[i].redir));
				printredir(tk_list[i].redir, pipes[i]);
				printredir(ft_redirlast(tk_list[i].redir), pipes[i]); */
			}
			else
			{
				av = get_av(pipes[i], j);//funcion q saca un arg, teniendo en cuenta q este primer char puede ser ' o ";
				//ft que hace addback al av
				
				//j += ft_strlen(av); esto esta puesto lo ultimo por si peta el bucle
				//free(av);
			}
			j++;
		}
		//tk->argc = lstsize(argv);
		//tk->argv[ac_ind] = NULL; para poner fin al array
		i++;
	}
	//printredir(tk_list->redir, data->user_input);
	tk_list[i].type = NONE;
	return (tk_list);
}


//esto de abajo es el bucle antiguo
/* 	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		tk_inrd(&tk_list[i], pipes[i]);
		tk_outrd(&tk_list[i], pipes[i]);
		if (tk_list[i].redir && tk_list[i].redir->type)
		{
			pipes[i] = rd_strdel(&tk_list[i], pipes[i]);
			printf("str = %s\n", pipes[i]);
		}
		tk_get_arg(&tk_list[i], pipes[i], env, data);
		i++;
	} */

	/*t_token	*tk_list_make(char **pipes, t_list *env, t_data *data)
{
	int		i;
	t_token	*tk_list;

	i = 0;
	while (pipes[i])
		i++;
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i = 0;
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		tk_inrd(&tk_list[i], pipes[i]);
		tk_outrd(&tk_list[i], pipes[i]);
		if (tk_list[i].redir && tk_list[i].redir->type)
		{
			while (tk_list[i].redir->next)
			{
				pipes[i] = rd_strdel(tk_list[i].redir, pipes[i]);
				tk_list[i].redir = tk_list[i].redir->next;
			}
			
			printf("str = %s\n", pipes[i]);
		}
		tk_get_arg(&tk_list[i], pipes[i], env, data);//<output echo "Hola""Hol ita" "Hola"
		i++;
	}
	tk_list[i].type = NONE;
	return (tk_list);*/