/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:38:10 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/07 14:39:10 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************
*This PROMPT is exclusive for 42MALAGA CAMPUS computers*
*******************************************************/
char	*ms_prompt(t_data *data)
{
	char	*prompt; //USER
	char	*char_aux;//SESSION_MANAGER
	t_list	*aux;
	int		i;
	int		start;
	i = 0;
	start = 0;
	aux = find_key(data->exported_list, "USER");//almacena USER en aux (t_list)

	if (aux != NULL)
		prompt = ft_strjoin(ft_strdup(aux->value), "@");//añade al prompt el valor(char *) de USER
	else
		prompt = ft_strjoin(ft_strdup("try_harder"), "@");//si USER no existe, es porque te has pasado de listillo

	aux = find_key(data->exported_list, "SESSION_MANAGER");//almacena un nuevo t_list, para buscar el ordenador que estamos usando en 42
	if (aux != NULL)
	{
		char_aux = ft_strjoin(ft_strdup(aux->value), "");//añade al char_aux el valor(char *) de SESSION_MANAGER al completo
		while(ft_isalpha(char_aux[i]) != 0)//buscamos donde empieza el cluster (cxrxsx)
			i++;
		start = i + 1;
		while(char_aux[i] != '.')//buscamos donde termina ya que el r puede valer una o dos cifras
			i++;
		char_aux = ft_substr(char_aux, start, (i - start));//recortamos solo lo que nos interesa.
	}
	else
		char_aux = "harder!!";
	prompt = ft_strjoin(prompt, ft_strjoin(char_aux, ":"));//añadimos el ordenador al usuario
	
	aux = find_key(data->exported_list, "PWD");//almacena un nuevo t_list, buscando donde nos encontramos
	if (aux)
		char_aux = ft_strjoin(ft_strdup(aux->value), "");//añade al char_aux el valor(char *) de PWD al completo
	else
		char_aux = getcwd(NULL, 0); //conseguimos la ruta -> /home/user/...
	i = 0;
	while(char_aux[start] && i < 1)
	{
		if (char_aux[start] == '/')
			i++;
		start++;
	}
	start--;
	i = start;
	while (char_aux[i])
		i++;
	start++;
	prompt = ft_strjoin(prompt, "~");
	if ((i - start) > 0)
	{
		char_aux = ft_substr(char_aux, start, (i - start));
		prompt = ft_strjoin(ft_strjoin(prompt, "/"), char_aux);
	}
	prompt = ft_strjoin(prompt, "$ ");
	return(prompt);
}