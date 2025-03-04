/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:56:47 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/03/04 10:49:07 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**********************************************************
*Check that every quote has start and end; and removes it.*
*It keeps the quotes if it's preced by a slash '\"'       *
**********************************************************/
static char	*bi_rm_quotes(char *argv)
{
	if (argv[0] == '"')
		argv++;
	printf("argv[0] = %c\n", argv[0]);
	if (argv[ft_strlen(argv) - 1] == '"')
		argv[ft_strlen(argv) - 1] = '\0';
	return (argv);
}

/**************************************************************************
* When called, ECHO will return the text you give.                        *
* If any data is stored it could read it:                                 *
*	name="Patricio" echo "Hi, your name is $name."                        *
* Also con print commands and ENV data.                                   *
*	echo "Date: $(date), User: $USER"                                     *
*If the option "-n" it's included, doesn't print the next line at the end.*
**************************************************************************/
int	bi_echo(t_token *token, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strncmp(token->argv[1], "-n", ft_strlen(token->argv[1])) == 0)
	i = 1;
	while (token->argv[++i])
	{
		token->argv[i] = bi_rm_quotes(token->argv[i]);
		printf("%s", token->argv[1]);
	}
	if (data)
		i = 1;



	write(1, "\n", 1);
	return (0);
}