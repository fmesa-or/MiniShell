/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:13:54 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 21:25:11 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//esto libera arrays dobles
void	free_2ptr(char **array, t_data *data)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		sfree(array[i], data);
		i++;
	}
	sfree(array, data);
}

//esto libera solo las struct de redirecciones
void	ft_redirclear(t_redir **red, t_data *data)
{
	t_redir	*aux1;
	t_redir	*aux2;

	aux1 = *red;
	if (red)
	{
		while (aux1)
		{
			aux2 = aux1->next;
			sfree(aux1->file, data);
			sfree(aux1, data);
			aux1 = aux2;
		}
		*red = NULL;
	}
}

void	ft_tokenclear(t_token *tk, t_data *data)
{
	if (tk->command)
	{
		sfree(tk->command, data);
		tk->command = NULL;
	}
	if (tk->argv)
		free_2ptr(tk->argv, data);
	if (tk->av_list)
		ft_envclear(&tk->av_list, data);
	if (tk->redir)
		ft_redirclear(&tk->redir, data);
}

//esto libera el env
void	ft_envclear(t_list **lst, t_data *data)
{
	t_list	*ls1;
	t_list	*ls2;

	ls1 = *lst;
	if (lst)
	{
		while (ls1)
		{
			ls2 = ls1->next;
			sfree(ls1->key, data);
			if (ls1->value)
				sfree(ls1->value, data);
			sfree(ls1, data);
			ls1 = ls2;
		}
		*lst = NULL;
	}
}

//esto libera parte de la estruct data para cada vez que se vuelve a mandar nueva linea
void	free_partial_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmnds)
	{
		free_2ptr(data->cmnds, data);
		data->cmnds = NULL;
	}
	if (data->user_input)
	{
		sfree(data->user_input, data);
		data->user_input = NULL;
	}
}

//esto libera todo eldata para cuando se va  a cerrar el programa;
	//LLamar a esto en exit
void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	free_partial_data(data);
	if (data->pwd)
	{
		sfree(data->pwd, data);
		data->pwd = NULL;
	}
	if (data->home)
	{
		sfree(data->home, data);
		data->home = NULL;
	}
	if (data->exported_list)
		ft_envclear(&data->exported_list, data);
}
