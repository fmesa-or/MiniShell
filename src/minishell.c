/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:21 by rmarin-j          #+#    #+#             */
/*   Updated: 2025/05/22 23:57:55 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;
	char	*a;

	i = 0;
	a = (char *)str;
	while (i < len)
	{
		a[i] = c;
		i++;
	}
	return (a);
}

/*
static void	copy_void_memory(void *dest, const void *src, size_t n)
{
	unsigned char *d;
	const unsigned char *s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	size_t i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}*/

t_data	*data_init(t_list *env)
{
	t_data	*data_list;
	t_list	*node;

	data_list = malloc(sizeof(t_data));
	if (!data_list)
	{
		throw_error("ERROR: data_init malloc dramatic failure", NULL, NULL);
		exit(errno);
	}
//	copy_void_memory(data_list->fd_table, pre_data->fd_table, sizeof(data_list->fd_table));
//	copy_void_memory(data_list->mem_table, pre_data->mem_table, sizeof(data_list->mem_table));
	ft_memset(data_list->fd_table, 0, sizeof(data_list->fd_table));
	ft_memset(data_list->mem_table, 0, sizeof(data_list->mem_table));
	data_list->l_status = 0;
	data_list->cmnds = NULL;
	data_list->exported_list = env;
	data_list->user_input = NULL;
	data_list->bk_in = sdup(STDIN_FILENO, data_list);
	data_list->bk_out = sdup(STDOUT_FILENO, data_list);
	data_list->file_in = 0;
	data_list->file_out = 1;
	node = find_key(env, "PATH");
	if (!node)
		throw_error("ERROR: PATH has been deleted", NULL, data_list);
//	data_list->pwd = ft_strdup(node->value);
//	data_list->pwd = (char*)smalloc(sizeof(getcwd), data_list);
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
	data_list->home = ft_strdup(node->value, data_list);
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
			sfree(data->user_input, data);
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
		ms_main_exe(tk_list, data);
	}
}

int main(int argc, char **argv, char **env)
{
	t_data	*data;
//	t_data	*pre_data;
	t_list	*list;
	int		final_status;

	data = NULL;
	list = NULL;
	final_status = 0;
	if (!env[0])
	{
		throw_error("ERROR: Enviroment not found.", NULL, NULL);
		exit(errno);
	}
	//Efectivamente en el momento de almacenar en list, es cuando metemos los datos extras.!!
//	while(list)
//	{
//		printf("ENV: %s=%s\n\n", list->key, list->value);
//		list = list->next;
//	}
//	list = temp;
	if (argc == 1 && argv)
	{
//		pre_data = pre_data_init();
		list = envtolist(env);
		data = data_init(list);//luego mandaremos los datos de predata y los copiaremos en data
		//		free(pre_data);
		//		free(data); //ESTO HACIA QUE PETASE
		mini_loop(data, list);
		final_status = data->l_status;
//		free_all_data(data);
	}
	sexit(final_status, data);
}
