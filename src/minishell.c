/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/09 20:23:27 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	
	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1 && argv)
	{
		t_list *list =envtolist(env);
		char *s= expand_var("$_ pito \\$PATH algarroba $", list);
		write(1, s, ft_strlen(s));
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
