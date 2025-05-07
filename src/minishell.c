/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/07 14:38:21 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

t_data	*data_init(t_list *env)
{
	t_data	*data_list;
	t_list	*node;

	data_list = malloc(sizeof(t_data));
	if (!data_list)
		throw_error("ERROR: ", NULL, NULL);	
	data_list->l_status = 0;
	data_list->cmnds = NULL;
	data_list->exported_list = env;
	data_list->user_input = NULL;
	data_list->bk_in = dup(STDIN_FILENO);
	data_list->bk_out = dup(STDOUT_FILENO);
	node = find_key(env, "PATH");
	if (!node)
		throw_error("ERROR: PATH has been deleted", NULL, data_list);
//	data_list->pwd = ft_strdup(node->value);
//	data_list->pwd = (char*)malloc(sizeof(getcwd));
	data_list->pwd = getcwd(NULL, 0);
	if (data_list->pwd == NULL)
		throw_error("ERROR: failed to set pwd", NULL, data_list);
//	printf("PWD: %s\n", data_list->pwd);
	node = find_key(env, "HOME");
	if (!node)
		throw_error("ERROR: HOME has been deleted", NULL, data_list);
	data_list->home = ft_strdup(node->value);

	return (data_list);
}



void	mini_loop(t_data *data, t_list *list)
{
	t_token	*tk_list;
	char	*prompt;

	
//	dprintf(2, GR"g_signal: %d\n"RES, g_signal);
	setup_signal_handlers();
	while (1)
	{
		
		prompt = ms_prompt(data);
		data->user_input = readline(prompt); //el prompt debería ser ~user:current_dir$~
		if (g_signal == SIGINT)
		{
			data->l_status = 130;
			g_signal = 0;
		}
//		else if (data->user_input[0] == '\0')
//			continue ;
		if (!data->user_input)
			break ;
		add_history(data->user_input);
		tk_list = parse_main(data->user_input, list, data);
		ms_main_exe(tk_list, data); //ls -l | grep docs | wc -l
	/* 	if (ft_strcmp(tk_list->command, "exit"))
			ft_exit(NULL); */
//		ft_tokenclear(tk_list); /*/aquí peta, REVISAR
//		free_partial_data(data);
	//	rl_on_new_line();
	//	rl_redisplay();
	}
}

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_list	*list; 
	t_list	*temp;

	if (!env[0])
		throw_error("ERROR: Enviroment not found.", NULL, NULL);


	list = envtolist(env);

	//Efectivamente en el momento de almacenar en list, es cuando metemos los datos extras.!!
	temp = list;
//	while(list)
//	{
//		printf("ENV: %s=%s\n\n", list->key, list->value);
//		list = list->next;
//	}
//	list = temp;


	if (argc == 1 && argv)
	{
		data = data_init(list);
//		write(1, "1\n", 2);//check
//		free(data); //ESTO HACIA QUE PETASE
		parse_main("", list, data);
//		parse_main("export >     flauta  3| algarroba $USER >   cebolla pwd|>> pollo wc -l tres", list, data);
		mini_loop(data, list);
		free_all_data(data);
	}
	return (0);
}
