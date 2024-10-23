/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:50 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/23 16:03:24 by rmarin-j         ###   ########.fr       */
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

/*esto mira q un caracter sea alfanumerico,
pa comprobar q despues de ciertos caracteres especiales
no van cosas raras como unas comilla o yo q se*/

int	ft_isalnum(int c)
{
	if (!c)
		return (0);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*esta funcion busca un caracter dentro de un str y devuelve el indice donde lo encuentra.
Sino lo encuentra devuelve -1;*/

int ft_strchr(const char *str, char c)
{
	char	*p;
    int     i;

    i = 0;
	p = (char *)str;
	while (p[i] != c && p[i] != '\0')
		i++;
	if (p[i] == c)
		return (i);
	return (-1);
}



/*Esta funcion le pasamos un str cuando el indice esta
	en una comilla y devuelve el mismo indice pero con
	el final de la comilla o salta error si termina el str*/

int	end_quote(char *str, int i, char c)
{
	while (str[i] && str[i] != c)
		i++;
	if(!str[i])
		throw_error("ERROR: ");
	return (i);
}