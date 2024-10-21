/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:05 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/16 19:23:37 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*tk_readrd(t_token *tk_node, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '<');
		if (str[i] == '<' && str[i+1] == '<')
		{
			tk_node->redir->type = HDOC;
			//coger aqui nombre del archivo?
			i += 2;			
		}
		else if(str[i] == '<' && str[i+1] != '<')
		{
			tk_node->redir->type = IN;
			i++;
		}
		else if (str[i] != '<' && str[i])
			i++;
	}
	return (tk_node);
}
t_token	*tk_writerd(t_token *tk_node, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i = pipe_iteri(str, i, '<');
		if (str[i] == '>' && str[i+1] == '>')
		{
			tk_node->redir->type = DOUT;
			//coger aqui nombre del archivo?
			i += 2;			
		}
		else if(str[i] == '>' && str[i+1] != '>')
		{
			tk_node->redir->type = NDOUT;
			i++;
		}
		else if (str[i] != '>' && str[i])
			i++;
	}
	return (tk_node);
}

t_token	*tk_list_make(char **pipes)
{
	int	i;

	i = 0;
	t_token	*tk_list;
	while (pipes[i])
	{
		tk_list= tk_init();
		//tk_readrd(tk_list, pipes[i]);
		//tk_writerd(tk_list, pipes[i]);
		tk_list = tk_list->next;
		i++;
	}
	return(tk_list);
}


