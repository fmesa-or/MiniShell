/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/24 22:07:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	data_init(t_data *data, t_list *env)
{
	t_list	*node;

	data->l_status = 0;
	data->cmnds = NULL;
	data->exported_list = env;
	data->user_input = NULL;
	data->bk_in = sdup(STDIN_FILENO);
	data->bk_out = sdup(STDOUT_FILENO);
	data->file_in = 0;
	data->file_out = 1;
	node = find_key(env, "PATH");
	if (!node)
		throw_error("ERROR: PATH has been deleted", NULL, data);
//	data->pwd = ft_strdup(node->value);
//	data->pwd = (char*)malloc(sizeof(getcwd));
	data->pwd = get_cwd();
	data->oldpwd = get_cwd();
	if (data->pwd == NULL)
		throw_error("ERROR: failed to set pwd", NULL, data);
//	printf("PWD: %s\n", data->pwd);
	node = find_key(env, "HOME");
	if (!node)
	{
		throw_error("ERROR: HOME has been deleted", NULL, data);
		exit (0);
	}
	data->home = ft_strdup(node->value);
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

	(void) prompt;
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
	t_data	data;
	t_list	*list;
	int		final_status;

	final_status = 0;
	ft_memset(&data, 0, sizeof(data));
	get_pdata(&data);
	if (!env[0])
	{
		throw_error("ERROR: Enviroment not found.", NULL, NULL);
		sexit(errno);
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
		data_init(&data, list);
		mini_loop(&data, list);
		final_status = data.l_status;
		free_all_data(&data);
	}
	sexit(final_status);
}
