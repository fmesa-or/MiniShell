/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/23 19:07:31 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printredir(t_redir *red, char *str)
{
	if (!red)
		write(1, "nope\n", 5);
	else{
	printf("cheking: %s\n", str);
	printf("file: %s\n", red->file);
	printf("tipo: %i\n", red->type);
	}
}

void tk_init(t_token *new)
{

	//new = malloc(sizeof(t_token));
	new->command = NULL;
	new->redir = NULL;
	new->argv = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
}

/*Esta funcion solo coge la siguiente palabra despues
de la redireccion, q tiene q ser el archivo al q hace ref*/

char *getfilename(char *str, int i)
{
	int	start;

	while(ft_isspace(str[i]) && str[i])
		i++;
	start = i;
	if (!str[i])
		return(NULL);
	else if (str[i] == '\"')
	{
		i = end_quote(str, i + 1, '\"');
		return(ft_substr(str, start, i - start));
	}
	else if (str[i] == '\'')
	{
		i = end_quote(str, i + 1, '\'');
		return(ft_substr(str, start, i - start));
	}
	else
	{
		while (!ft_isspace(str[i]) && str[i])
			i++;
		printf("i = %i\nstart = %i\n", i, start);
		return(ft_substr(str, start, i - start));
	}
}

void	tk_inrd(t_token *tk_node, char *str)
{
	int i;
	t_redir *aux_red;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '<');
		if(!str[i])
			break ;
		printf("inrd: %s\n", &str[i]);
		if (str[i] == '<' && str[i+1] == '<')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = HDOC;
			aux_red->file = getfilename(str, i + 2);
			printf("%s\n", aux_red->file);
			i += 2;			
		}
		else if(str[i] == '<' && str[i+1] != '<')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = IN;
			aux_red->file = getfilename(str, i + 1);
			printf("%s\n", aux_red->file);
			i++;
		}
		else if (str[i] != '<' && str[i])
			i++;
	}
	printredir(tk_node->redir, "in");
}
void	tk_outrd(t_token *tk_node, char *str)
{
		int i;
	t_redir *aux_red;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '>');
		if(!str[i])
			break ;
		printf("outrn: %s\n", &str[i]);
		if (str[i] == '>' && str[i+1] == '>')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = NDOUT;
			aux_red->file = getfilename(str, i + 2);
			printf("%s\n", aux_red->file);
			i += 2;			
		}
		else if(str[i] == '>' && str[i+1] != '>')
		{
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = DOUT;
			aux_red->file = getfilename(str, i + 1);
			printf("%s\n", aux_red->file);
			i++;
		}
		else if (str[i] != '>' && str[i])
			i++;
	}
	printredir(tk_node->redir, "out");
}

t_token	*tk_list_make(char **pipes)
{
	int	i;

	i = 0;
	t_token	*tk_list;
	while (pipes[i])
		i++;
	tk_list = malloc(sizeof(t_token) * (i + 1));
	i  = 0;	
	while (pipes[i])
	{
		tk_init(&tk_list[i]);
		tk_inrd(&tk_list[i], pipes[i]);
		tk_outrd(&tk_list[i], pipes[i]);	
		//tk_list = tk_list->next;
		i++;
	}
	return(tk_list);
}


