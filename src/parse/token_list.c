/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/19 18:23:32 by rmarin-j         ###   ########.fr       */
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

void	tk_argvtipe(t_token *tk_list, t_list *env, t_data *data)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = 0;
	while (tk_list->argv[i])
	{
		if (is_builtin(tk_list, tk_list->argv[i]))
			flag ++;
		else if (is_cmd(tk_list->argv[i], tk_list, env, data))
			flag++;
		i++;
	}
	if (flag == 0)
		throw_error("ERROR: no cmd in pipe\n", tk_list, data);
	else if (flag > 1)
		throw_error("ERROR: too much cmd in pipe\n", tk_list, data);
	tk_list->argc = i;
}

/*--------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------*/

 int	ft_lstsize(t_list *lst)
 {
 	t_list	*node;
 	int		count;

 	count = 0;
 	node = lst;
 	//if (!node)
 		//printf("\nno redir en lstsize\n");
 	while (node)
 	{
 		count++;
 		node = node->next;
 	}
 	return (count);
 }
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
		//printf("\nav quot[%i] = %s\n", j, av);
		ft_lstadd_back(lst, ft_lstnew(av, "q")); //le dejo una q en el value para marcar quoted
		printf("\nav node quot[%i] = %s\n", j, av);
		return(j + 1);//aqui devuelve con comillas
	}
	else
	{
		while (!ft_isspace(str[j]) && str[j])
			j++;
		av = ft_substr(str, start, j - start);
		//printf("\nav normal [%i] = %s\n", j, av);
		ft_lstadd_back(lst, ft_lstnew(av, NULL));
		printf("\nav node normal[%i] = %s\n", j, (*lst)->key);
		return (j);
	}
}
void print2char(char **str)
{
	int i = 0;

	write(1, "print2char\n", 12);
	while (str[i])
	{
		write(1, str[i], strlen(str[i]));
		write(1, "\n", 1);
		i++;
	}
}


t_token	*tk_list_make(char **pipes, t_list *env, t_data *data)
{
	int		i;
	int		j;
	//int		ac_ind; //esto sera el indice de tk->argv
	//char	*av;
	t_token	*tk_list;

	i = sizeof(env[3]);
	i = 0;
	j = data->l_status;
	j = 0;
	while (pipes[i])
	{
		write(1, pipes[i], ft_strlen(pipes[i]));
		write(1, "\n", 1);
		i++;
	}
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i = 0;
	
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		//tk->ac = funcion q haya el argc y me genera array de argv
		//ac_ind = 0;  ya q se reinicia en cada tk
		j = 0;
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
			
			else if (pipes[i][j] && (pipes[i][j] != '<' && pipes[i][j] != '>' && !ft_isspace(pipes[i][j])))
			{
				j = get_av(&tk_list[i].av_list, pipes[i], j);//funcion q saca un arg, teniendo en cuenta q este primer char puede ser ' o ";
				//printf("tamaño = %i, av tras ft = %s\n", ft_lstsize(tk_list[i].av_list), tk_list[i].av_list->key);
			}
			//j++;
		}
		tk_list[i].argv = listtoargv(tk_list[i].av_list);
		tk_argvtipe(&tk_list[i], env, data);
		printf("\nargc = %i --- tipo del tk = %i\n", tk_list[i].argc, tk_list[i].type);
		print2char(tk_list[i].argv);
		write(1, "\nfin tk\n\n", 10);
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

