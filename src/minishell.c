/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/10/21 15:56:59 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(t_list *env)
{
	t_data *data_list;
	t_list *node;

	data_list = malloc(sizeof(t_data));
	if (!data_list)
		throw_error("ERROR: ");	
	data_list->l_status = 0;
	data_list->cmnds = NULL; //esta linea y la de arriba cambiaran
	data_list->exported_list = env;
	data_list->user_input = NULL;
	node = find_key(env, "PATH");
	data_list->pwd = ft_strdup(node->value);
	node = find_key(env, "HOME");
	data_list->home = ft_strdup(node->value);
	
	return(data_list);
}


void	mini_loop(t_data *data, t_list *list)
{
	
	while (1)
	{
		data->user_input = readline("minishell> "); //el prompt debería ser ~user:current_dir$~
		if (!data->user_input)
			break ;
		add_history(data->user_input);
		parse_main(data->user_input, list);

		//printf("Input: %s\n", line); //aquí debería ir la función que parsea la línea
		free(data->user_input);
	//	rl_on_new_line();
	//	rl_redisplay();
	}
}

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_list *list = envtolist(env);

	if (!env[0])
		throw_error("ERROR: ");
	if (argc == 1 && argv)
	{
		data = data_init(list);
		free(data);
		parse_main("pito flaut|as florin$USER", list);
		//mini_loop(data,list);
		//write(1, s, ft_strlen(s));
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
