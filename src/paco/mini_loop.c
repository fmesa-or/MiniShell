/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:16:42 by fmesa-or          #+#    #+#             */
/*   Updated: 2024/10/03 17:49:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_loop()
{
	char	*line;

	while (1)
	{
		line = readline("minishell> "); //el prompt debería ser ~user:current_dir$~
		if (!line)
			break ;
		if (*line)
			add_history(line);
		printf("Input: %s\n", line);
		free(line);
		rl_on_new_line();
		rl_redisplay();
	}
}