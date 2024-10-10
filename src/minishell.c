/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/10 14:23:17 by rmarin-j         ###   ########.fr       */
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
		printf("Input: %s\n", line); //aquí debería ir la función que parsea la línea
		free(line);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char **argv, char **env)
{
	
	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1 && argv)
	{
		mini_loop();
		/* t_list *list =envtolist(env);
		char *s= expand_var("$_ pito \\$PATH algarroba $", list);
		write(1, s, ft_strlen(s));
		write(1, "\n", 1); */

		//write(1, av[3], ft_strlen(av[3]));
		//write(1, "\n", 1);
		//write(1, list->value, ft_strlen(list->value));
		//write(1, "\n", 1);
		//write(1, list->next->value, ft_strlen(list->next->value));
		//write(1, "\n", 1);
		//write(1, list->next->next->value, ft_strlen(list->next->next->value));
		//write(1, "\n", 1);
	}
	return (0);
}
