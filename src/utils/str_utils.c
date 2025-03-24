/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:50 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/03/24 11:17:47 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Esto imprime str por el fd deseado*/
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}


/*Esta funcion mira q un char sea un espacio.
	Se usa dentro de la condicion de los while*/
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c =='\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return(1);
	else
		return(0);
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



/*Esta funcion le pasamos la i+1, un str cuando el indice esta
	en una comilla y devuelve el mismo indice pero con
	el final de la comilla o salta error si termina el str*/
int	end_quote(char *str, int i, char c)
{
	/* if(str[i] == c)
		return (i); */
	while (str[i] != c && str[i])
		i++;
	if (!str[i])
		throw_error("ERROR: no ended quote", NULL, NULL);
	return (i);
}