/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/07 15:05:22 by rmarin-j         ###   ########.fr       */
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
		ft_export(list, "_=pene");
		ft_env(list);
		//write(1, list->value, ft_strlen(list->value));
		//write(1, "\n", 1);
		//write(1, list->next->value, ft_strlen(list->next->value));
		//write(1, "\n", 1);
		//write(1, list->next->next->value, ft_strlen(list->next->next->value));
		//write(1, "\n", 1);
	}
	return (0);
}
