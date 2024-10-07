/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:13:43 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/07 19:08:07 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esta funcion comprueba que las comillas o el caracter que sea esta cerrado;
	basicamente, mira si hay un numero par del caracter de turno, y entonces devuelve 0;
	sino, devuelve -1 como q esta abierta una comilla.
	Habria q pasarla una vez por cada caracter q se quiera comprobar.
	Tiene en cuenta q si el char es '<' luego mira el de cierre*/
/* int	close_quote(char *str, char c)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			count++;
			if(c == '<')
				c = '>';
			else if (c == '>')
				c = '<';
		}
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (-1);

} */



/*comprobar q cuenta bien, tiene q contar los cachos entre |,
sin tener en cuenta los entre comillas y eso*/
int	pipe_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i] )
	{
		if(str[i] == '\\' && str[i+1])
			i++;
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
		else if (str[i] == '|')
			count++;
		count++;
		i++;
	}
	return(count);
}

void	parse_main(char *str)
{
	char **av;

	pipe_count(str);
	av = pipe_separator(str);
}

