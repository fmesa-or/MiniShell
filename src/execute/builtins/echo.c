/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:56:47 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/03/04 20:34:08 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************
*Counts the quotes of the full argv*
***********************************/
static int	bi_c_quote(char *str)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = -1;
//	printf("\nCHECK bi_c_quotes\n");
	while (str[++i])
	{
		if (str[i] == '\"')
			quotes++;
	}
//	printf("nº of quotes: %d\n", quotes);
	return (quotes);
}

/**********************************************************
*Check that every quote has start and end; and removes it.*
*It keeps the quotes if it's preced by a slash '\"'       *
**********************************************************/
static char	*bi_rm_quotes(char *argv)
{
	int	i;
	int	j;
	int	q;
	char *aux;

	i = 0;
	j = 0;
//	printf("CHECK bi_rm_quotes\n");
	q = bi_c_quote(argv);
	if (q % 2 != 0)
		while (1)
			i = 1;
	else
	{
		aux = (char *)malloc((sizeof(char *)) * (ft_strlen(argv) - q + 1));
		while (argv[i])
		{
			if (argv[i + j] == '"')
				j++;
			aux[i] = argv[i + j];
			i++;
		}
		free(argv);
	}
	return (aux);
}

/**************************************************************************
* When called, ECHO will return the text given.                           *
* If any data is stored it could read it:                                 *
*	name="Patricio" echo "Hi, your name is $name."                        *
* Also con print commands and ENV data.                                   *
*	echo "Date: $(date), User: $USER"                                     *
*If the option "-n" it's included, doesn't print the next line at the end.*
*If there is no arguments for "echo" it should return a newline.          *
**************************************************************************/
int	bi_echo(t_token *token)
{
	int	i;

	i = 0;
//	printf ("CHECK bi_echo\n");

	if (ft_strncmp(token->argv[1], "-n", ft_strlen(token->argv[1])) == 0)
	{
		i = 1;
		if (!(token->argv[2]))//no funciona del todo bien, REVISAR
		{
			write(token->fd[1], "\n", 1);
			return (0);
		}
		while (token->argv[++i])
		{
			token->argv[i] = bi_rm_quotes(token->argv[i]);
			write(token->fd[1], token->argv[i], ft_strlen(token->argv[i]));
			if (token->argv[i + 1])
				write(token->fd[1], " ", 1);
		}
	}

	else
	{
		if (!(token->argv[1]))
		{
			write(token->fd[1], "\n", 1);
			return (0);
		}
		while (token->argv[++i])
		{
			token->argv[i] = bi_rm_quotes(token->argv[i]);
			write(token->fd[1], token->argv[i], ft_strlen(token->argv[i]));
			if (token->argv[i + 1])
				write(token->fd[1], " ", 1);
		}
		write(token->fd[1], "\n", 1);
	}
	return (0);
}
