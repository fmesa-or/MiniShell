/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/12/16 12:49:05 by fmesa-or         ###   ########.fr       */
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
	if(!node)
		throw_error("ERROR: PATH has been deleted");
	data_list->pwd = ft_strdup(node->value);
	node = find_key(env, "HOME");
	if(!node)
		throw_error("ERROR: HOME has been deleted");
	data_list->home = ft_strdup(node->value);
	
	return(data_list);
}


void	mini_loop(t_data *data, t_list *list)
{
	t_token	*tk_list;

	while (1)
	{
		data->user_input = readline("minishell> "); //el prompt debería ser ~user:current_dir$~
	//	write(1, "2\n", 2);
		if (!data->user_input)
			break ;
		add_history(data->user_input);
	//	write(1, "3\n", 2);
		tk_list = parse_main(data->user_input, list, data);
	//	write(1, "4\n", 2);
		ft_execute(tk_list, data);//aqui va la ejecucion
		//printf("Input: %s\n", line); //aquí debería ir la función que parsea la línea
	/* 	if (ft_strcmp(tk_list->command, "exit"))
			ft_exit(NULL); */
		ft_tokenclear(tk_list);
		free_partial_data(data);
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
	//	write(1, "1\n", 2);
		//free(data);
		//parse_main("export >     flauta  3| algarroba $USER >   pene pwd|>> polla wc -l tres", list, data);
		mini_loop(data,list);
	}
	free_all_data(data);
	return (0);
}
