/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:13:54 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/04 12:38:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//esto libera arrays dobles
void	free_2ptr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	else if (ft_strncmp(array[0], "", ft_strlen(array[0])) != 0)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

//esto libera solo las struct de redirecciones
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
			free(aux1->file);
			free(aux1);
			aux1 = aux2;
		}
		*red = NULL;
	}
}

void	ft_tokenclear(t_token *tk)
{
	if (tk->command)
	{
		free(tk->command);
		tk->command = NULL;
	}
	if (tk->argv)
		free_2ptr(tk->argv);
	if (tk->redir)
		ft_redirclear(&tk->redir);
	if (tk->env)
		ft_envclear(&tk->env);
}

//esto libera el env
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
			free(ls1->key);
			free(ls1->value);
			free(ls1);
			ls1 = ls2;
		}
		*lst = NULL;
	}
}

//esto libera parte de la estruct data para cada vez que se vuelve a mandar nueva linea
void	free_partial_data(t_data *data)
{
	if (data->cmnds)
	{
		free_2ptr(data->cmnds);
		data->cmnds = NULL;
	}
	if (data->user_input)
	{
		free(data->user_input);
		data->user_input = NULL;
	}
}

//esto libera todo eldata para cuando se va  a cerrar el programa;
	//LLamar a esto en exit
void	free_all_data(t_data *data)
{
	free_partial_data(data);
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->home)
	{
		free(data->home);
		data->home = NULL;
	}
	if (data->exported_list)
		ft_envclear(&data->exported_list);
}
