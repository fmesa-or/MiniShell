/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:13:43 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/20 19:19:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Esta funcion itera el str hasta encontrar un pipe valido.
	Despues devuelve el int de su posicion, lo q sirve para retomar ese valor*/
int	pipe_iteri(char *str, int i, char c)
{
	while (str[i] != c && str[i])
	{
		if(str[i] == '\\' && str[i+1])
			i += 2;
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		i++;
	}
	return (i);
}

/*Esta funcion cuenta los cachos entre |, sin tener en cuenta
los q esten entre comillas y eso.
IMPORTANTE: si hay una pipe como primer o ultimo  char los cuenta,
sendos casos tienen q tener tratamientos distintos:
	Si el str[0] = |, tiene q dar error como q el primer pipe ta vacio.
	Si el ultimo str[i] = |, tiene 	q dejar escribir el ultimo trozo por terminal;*/

int	pipe_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		i = pipe_iteri(str, i, '|');
		if (str[i] == '|')
			i++;	
	}
	return (count);
}

/*Esta funcion coge el string inicial q nos pasen y lo separa por pipes.
	Retorna char **, correspondiente a argv.
	Tiene en cuenta comillas simples, dobles, y la barra invertida.
	El tratamiento de las redir tendra q  ser previo o posterior a esta ft.
*/

char	**pipe_separator(char *str, t_data* data)
{
	char	**av;
	int	i;
	int	start;
	int	k;
	int	npipe;

	i = 0;
	start = 0;
	k = 0;
	npipe = pipe_count(str);
	av = malloc(sizeof(char *) * (npipe +1));
	if(!av)
	{
		throw_error("ERROR: malloc failed in bm_rm_quotes", NULL, data);//pasarle data y token si necesario
		exit(errno);
	}
	while (str[i])
	{
		start = i;
		i = pipe_iteri(str, start, '|');
		av[k] = ft_substr(str, start, i - start);
		if(str[i] == '|')
			i++;
		k++;
	}
	av[k] = NULL;
	return (av);
}

t_token	*parse_main(char *str, t_list *list, t_data *data)
{
	char	**av;
	char	*aux;
	t_token	*tokens;

	av = NULL;
	tokens = NULL;
	aux = expand_var(str, list, data, NULL);
	av = pipe_separator(aux, data);
/* 	while (av[i])
	{
		write(1, "\n---PIPE---\n", 13);
		write(1, av[i], ft_strlen(av[i]));
		write(1, "\n", 1);
		write(1, "\n---EPIP---\n", 13);
		i++;
	} */
	tokens = tk_list_make(av, list, data);
	free_2ptr(av);
	if (!tokens)
		return (NULL);
	return (tokens);
}
