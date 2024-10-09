/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:13:43 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/09 20:26:33 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion mira q un char sea un espacio.
	Se usa dentro de la condicion de los while*/
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c =='\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return(0);
	else
		return(1);
}
/*Esta funcion itera el str hasta encontrar un pipe valido.
	Despues devuelve el int de su posicion, lo q sirve para retomar ese valor*/
int	pipe_iteri(char *str, int i)
{
	while (str[i] != '|' && str[i])
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
	return(i);
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
	while(str[i])
	{
		count++;
		i = pipe_iteri(str, i);
		if (str[i] == '|')
			i++;	
	}
	return(count);
}

/*Esta funcion coge el string inicial q nos pasen y lo separa por pipes.
	Retorna char **, correspondiente a argv.
	Tiene en cuenta comillas simples, dobles, y la barra invertida.
	El tratamiento de las redir tendra q  ser previo o posterior a esta ft.
*/

char	**pipe_separator(char *str)
{
	char	**av;
	int	i;
	int	j;
	int	k;
	int	npipe;

	i = 0;
	j = 0;
	npipe = pipe_count(str);
	av = malloc(sizeof(char *) * npipe +1);
	if(!av)
		throw_error("ERROR: ");
	while (npipe > 0)
	{
		k = pipe_iteri(str, j);
		av[i] = ft_substr(str, j, k - j);
		j = k;
		if(str[j] == '|')
			j++;
		i++;
		npipe--;
	}
	av[i] = 0;
	return(av);	
}

void	parse_main(char *str, t_list *list)
{
	char **av;
	int	i;

	i = 0;
	pipe_count(str);
	av = pipe_separator(str);
	while (av[i])
	{
		av[i] = expand_var(av[i], list);
		i++;
	}

}

