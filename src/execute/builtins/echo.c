/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:56:47 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/05/24 22:28:08 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**************************************************************************
* When called, ECHO will return the text given.                           *
* If any data is stored it could read it:                                 *
*	name="Patricio" echo "Hi, your name is $name."                        *
* Also con print commands and ENV data.                                   *
*	echo "Date: $(date), User: $USER"                                     *
*If the option "-n" it's included, doesn't print the next line at the end.*
*If there is no arguments for "echo" it should return a newline.          *
**************************************************************************/
int	bi_echo(t_token *token, int *fd)
{
	int	i;

	(void) fd;
	i = 0;
	if (token->argv[1] && (ft_strncmp(token->argv[1],
				"-n", ft_strlen(token->argv[1])) == 0))
	{
		i = 1;
		while (token->argv[++i])
		{
			write(1, token->argv[i], ft_strlen(token->argv[i]));
			if (token->argv[i + 1])
				write(1, " ", 1);
		}
	}
	else
	{
		if (!(token->argv[1]))
		{
			write(1, "\n", 1);
			return (0);
		}
		while (token->argv[++i])
		{
//			dprintf(2, "CHECK: %s\n", token->argv[i]);
			write(1, token->argv[i], ft_strlen(token->argv[i]));
			if (token->argv[i + 1])
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (0);
}
