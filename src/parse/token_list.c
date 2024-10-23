/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/23 15:34:56 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printredir(t_redir *red, char *str)
{
	printf("cheking: %s\n", str);
	printf("file: %s\n", red->file);
	printf("tipo: %i\n", red->type);
}

t_token	*tk_init(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->command = NULL;
	new->redir = NULL;
	new->next = NULL;
	new->argv = NULL;
	new->argc = 0;
	new->pid = 0;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->l_status = 0;
	return (new);
}

/*Esta funcion solo coge la siguiente palabra despues
de la redireccion, q tiene q ser el archivo al q hace ref*/

char *getfilename(char *str, int i)
{
	int	start;

	write(1, "5\n", 2);
	while(ft_isspace(str[i]) && str[i])
		i++;
	start = i;
	if (!str[i])
		return(NULL);
	else if (str[i] == '\"')
	{
		i = end_quote(str, i, '\"');
		return(ft_substr(str, start, i - start));
	}
	else if (str[i] == '\'')
	{
		i = end_quote(str, i, '\'');
		return(ft_substr(str, start, i - start));
	}
	else
	{
		write(1, "6\n", 2);
		while (!ft_isspace(str[i]) && str[i])
			i++;
		write(1, "7\n", 2);
		return(ft_substr(str, start, i - start));
	}
}

t_token	*tk_inrd(t_token *tk_node, char *str)
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
			i += 2;			
		}
		else if(str[i] == '<' && str[i+1] != '<')
		{
			write(1, "9\n", 2);
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = IN;
			aux_red->file = getfilename(str, i + 1);
			i++;
		}
		else if (str[i] != '<' && str[i])
			i++;
	}
	printredir(tk_node->redir, "in");
	return (tk_node);
}
t_token	*tk_outrd(t_token *tk_node, char *str)
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
			i += 2;			
		}
		else if(str[i] == '>' && str[i+1] != '>')
		{
			write(1, "9\n", 2);
			aux_red = malloc(sizeof(t_redir));
			ft_rediradd_back(&tk_node->redir, aux_red);
			aux_red->type = DOUT;
			aux_red->file = getfilename(str, i + 1);
			i++;
		}
		else if (str[i] != '>' && str[i])
			i++;
	}
	printredir(tk_node->redir, "out");
	return (tk_node);
}

t_token	*tk_list_make(char **pipes)
{
	int	i;

	i = 0;
	t_token	*tk_list;
	t_token *head;
	while (pipes[i])
	{
		write(1, "1\n", 2);
		tk_list= tk_init();
		if(i = 0)
			head = tk_list;
		write(1, "2\n", 2);
		tk_inrd(tk_list, pipes[i]);
		write(1, "3\n", 2);
		tk_outrd(tk_list, pipes[i]);
		write(1, "4\n", 2);
		
		tk_list = tk_list->next;
		i++;
	}
	return(tk_list);
}


