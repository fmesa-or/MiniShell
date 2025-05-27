/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:13:43 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/27 19:19:45 by fmesa-or         ###   ########.fr       */
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
		{
			if (!str[i+1])
				count++;
			i++;	
		}
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
	av = smalloc(sizeof(char *) * (npipe +1));
	if (!av)
	{
		throw_error("ERROR: smalloc failed in bm_rm_quotes", NULL, data);//pasarle data y token si necesario
		sexit(errno);
	}
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		start = i;
		i = pipe_iteri(str, start, '|');
		av[k] = ft_substr(str, start, i - start);
		if (str[i] == '|')
		{
			if (!str[i+1])
			{
				k++;
				av[k] = ft_strdup("");
			}
			i++;
		}
		k++;
	}
	av[k] = NULL;
	return (av);
}

/*zero = void str; 1 = there's chars*/
int	str_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}


char	**check_pipes(char **pipes, t_data *data)
{
	int	i;

	i = 0;
	if (!pipes)
	{
		throw_error("ERROR: no pipes", NULL, data);
		return (NULL);
	}
	while (pipes[i])
	{
		if (!pipes[i][0] || str_isspace(pipes[i]) == 0)
		{
			pipes[i] = readline("> ");
		}
		i++;
	}
	return (pipes);
}

t_token	*parse_main(char *str, t_list *list, t_data *data)
{
	char	**av;
	char	*aux;
	t_token	*tokens;

	av = NULL;
	tokens = NULL;
	if (str[0] == '|')
	{
		throw_error("Minishell: syntax error near unexpected token", NULL, NULL);
		data->l_status = 2;
		return (NULL);
	}
	aux = expand_var(str, list, data, NULL);
	av = check_pipes(pipe_separator(aux, data), data);
	if (!av)
		return (NULL);
	tokens = tk_list_make(av, list, data);
	free_2ptr(av);
	if (!tokens)
		return (NULL);
	return (tokens);
}
