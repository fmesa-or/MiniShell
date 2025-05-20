/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/20 21:46:39 by fmesa-or         ###   ########.fr       */
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
	{
		throw_error("ERROR: ", NULL, NULL);	
		exit(errno);
	}
	data_list->l_status = 0;
	data_list->cmnds = NULL;
	data_list->exported_list = env;
	data_list->user_input = NULL;
	data_list->bk_in = dup(STDIN_FILENO);
	data_list->bk_out = dup(STDOUT_FILENO);
	data_list->file_in = 0;
	data_list->file_out = 1;
	node = find_key(env, "PATH");
	if (!node)
		throw_error("ERROR: PATH has been deleted", NULL, data_list);
//	data_list->pwd = ft_strdup(node->value);
//	data_list->pwd = (char*)malloc(sizeof(getcwd));
	data_list->pwd = getcwd(NULL, 0);
	data_list->oldpwd = getcwd(NULL, 0);
	if (data_list->pwd == NULL)
		throw_error("ERROR: failed to set pwd", NULL, data_list);
//	printf("PWD: %s\n", data_list->pwd);
	node = find_key(env, "HOME");
	if (!node)
	{
		throw_error("ERROR: HOME has been deleted", NULL, data_list);
		exit (0);
	}
	data_list->home = ft_strdup(node->value);
	return (data_list);
}



static int check_quote(char *str)
{
	int i;
	i = 0;
	while (str[i])
	{
		if(str[i] == '\"' || str[i] == '\'')
			i = end_quote(str,i + 1,str[i],NULL);
		if (i == -1)
			return(-1);
		i++;
	}
	return(0);
}

void	mini_loop(t_data *data, t_list *list)
{
	t_token	*tk_list;
	char	*prompt;


	setup_signal_handlers();
	while (1)
	{
		prompt = ms_prompt(data);
		data->user_input = readline("> "); //el prompt debería ser ~user:current_dir$~
		if (!data->user_input)
			break ;
		if (check_quote(data->user_input) == -1)
		{
			free(data->user_input);
			continue ;
		}
		if (g_signal == SIGINT)
		{
			data->l_status = 130;
			g_signal = 0;
		}
//		else if (data->user_input[0] == '\0')
//			continue ;
		add_history(data->user_input);
		tk_list = parse_main(data->user_input, list, data);
		ms_main_exe(tk_list, data); //ls -l | grep docs | wc -l
	/* 	if (ft_strcmp(tk_list->command, "exit"))
			ft_exit(NULL); */
//		ft_tokenclear(tk_list); /*/aquí peta, REVISAR
//		free_partial_data(data);
	//	rl_on_new_line();
	//	rl_redisplay();
//		free(prompt);
	}
}

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_list	*list;

	if (!env[0])
	{
		throw_error("ERROR: Enviroment not found.", NULL, NULL);
		exit(errno);
	}
	list = envtolist(env);
	//Efectivamente en el momento de almacenar en list, es cuando metemos los datos extras.!!
//	while(list)
//	{
//		printf("ENV: %s=%s\n\n", list->key, list->value);
//		list = list->next;
//	}
//	list = temp;
	if (argc == 1 && argv)
	{
		data = data_init(list);
		//		free(data); //ESTO HACIA QUE PETASE
		mini_loop(data, list);
		free_all_data(data);
	}
	return (0);
}
