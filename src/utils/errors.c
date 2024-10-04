/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:50:44 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/10/04 13:05:58 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(const char *str)
{
	perror(str);
	exit (errno);
}

/*Esta funcion comprueba que las comillas o el caracter que sea esta cerrado;
	basicamente, mira si hay un numero par del caracter de turno, y entonces devuelve 0;
	sino, devuelve -1 como q esta abierta una comilla.
	Habria q pasarla una vez por cada caracter q se quiera comprobar.
	Tiene en cuenta q si el char es '<' luego mira el de cierre*/
int	close_quote(char *str, char c)
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

}
