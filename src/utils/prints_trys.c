/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_trys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:48:13 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/13 13:54:45 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printredir(t_redir *red, char *str)
{
	if (!red)
		printf("la redir no existe\n");
	printf("\n---------------\n");
	printf("-----REDIR-----\n\n");
	printf("PIPE = [ %s ]\n", str);
	printf("rd--> tipo = %i,  file = %s\n", red->type, red->file);
	printf("---------------\n\n");
}

void	print2char(char **str)
{
	int	i;

	i = 0;
	write(1, "print2char\n", 12);
	while (str[i])
	{
		write(1, str[i], strlen(str[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	print_tokenlist(t_token *tk)
{
	int i;

	i = 0;
	printf("\n----------TOKEN LIST----------\n");
	while (&tk[i] && tk[i].type != NONE)
	{
		printf("tk[%i] :\n", i);
		if (tk[i].argv)
			print2char(tk[i].argv);
		i++;
	}
	printf("\n----------TOKEN ENDS----------\n\n");
}
