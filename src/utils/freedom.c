/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:13:54 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/29 18:35:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************************
*Free two pointer array.*
************************/
void	free_2ptr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		sfree(array[i]);
		i++;
	}
	sfree(array);
}

/***************************
*Frees the redir structure.*
***************************/
void	ft_redirclear(t_redir **red)
{
	t_redir	*aux1;
	t_redir	*aux2;

	aux1 = *red;
	if (red)
	{
		while (aux1)
		{
			aux2 = aux1->next;
			sfree(aux1->file);
			sfree(aux1);
			aux1 = aux2;
		}
		*red = NULL;
	}
}

void	ft_tokenclear(t_token *tk)
{
	if (tk->command)
	{
		sfree(tk->command);
		tk->command = NULL;
	}
	if (tk->argv)
		free_2ptr(tk->argv);
	if (tk->av_list)
		ft_envclear(&tk->av_list);
	if (tk->redir)
		ft_redirclear(&tk->redir);
}

/**********************
*Frees the enviroment.*
**********************/
void	ft_envclear(t_list **lst)
{
	t_list	*ls1;
	t_list	*ls2;

	ls1 = *lst;
	if (lst)
	{
		while (ls1)
		{
			ls2 = ls1->next;
			sfree(ls1->key);
			if (ls1->value)
				sfree(ls1->value);
			sfree(ls1);
			ls1 = ls2;
		}
		*lst = NULL;
	}
}

void	free_partial_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmnds)
	{
		free_2ptr(data->cmnds);
		data->cmnds = NULL;
	}
	if (data->user_input)
	{
		sfree(data->user_input);
		data->user_input = NULL;
	}
}
