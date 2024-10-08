/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/08 17:47:11 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	
	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1 && argv)
	{
		//t_list *list =envtolist(env);
		char **av = pip_separator("Hola \"av|p\" \\| adsc | cat");
		write(1, av[0], ft_strlen(av[0]));
		write(1, "\n", 1);
		write(1, av[1], ft_strlen(av[1]));
		write(1, "\n", 1);
		write(1, av[2], ft_strlen(av[2]));
		write(1, "\n", 1);
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
