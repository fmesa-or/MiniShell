/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:50 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/30 13:21:41 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

/***********************************************************************
* This function checks if a char is a space. It's used within the      *
* condition of while loops.                                             *
***********************************************************************/
int	ft_isspace(char c)
{
	if ((c == ' ' || c == '\t') || (c == '\n'
			|| c == '\r') || (c == '\f' || c == '\v'))
		return (1);
	else
		return (0);
}

/***********************************************************************
* This checks if a character is alphanumeric, to verify that after     *
* certain special characters there are no weird things like quotes or   *
* whatever.                                                             *
***********************************************************************/
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

/***********************************************************************
* This function searches for a character within a string and returns   *
* the index where it finds it. If it doesn't find it, it returns -1.   *
***********************************************************************/
int	ft_strchr(const char *str, char c)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)str;
	while (p[i] != c && p[i] != '\0')
		i++;
	if (p[i] == c)
		return (i);
	return (-1);
}

/***********************************************************************
* This function is passed i+1, a string when the index is at a quote  *
* and returns the same index but at the end of the quote or throws an  *
* error if the string ends.                                            *
***********************************************************************/
int	end_quote(char *str, int i, char c, t_token *tk)
{
	while (str[i] != c && str[i])
		i++;
	if (!str[i])
	{
		throw_error("ERROR: no ended quote", tk, NULL);
		return (-1);
	}
	return (i);
}
