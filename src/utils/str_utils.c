/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:50 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/22 15:52:41 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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