/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumar2 <migumar2@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:53:31 by jholland          #+#    #+#             */
/*   Updated: 2024/07/17 13:45:27 by migumar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	init_data(t_all *data, char **argv, char **env)
{
	data->pwd = NULL;
	data->prog_name = ft_substr(argv[0], 2, ft_strlen(argv[0]) - 2);
	data->exported_list = NULL;
	data->bk_in = dup(STDIN_FILENO);
	data->bk_out = dup(STDOUT_FILENO);
	data->last_status = 0;
	create_export_list(data, env);
	data->home = find_var(data->exported_list, "HOME");
}

void	minishell_loop(t_all *data)
{
	char	*line;
	t_token	*tokens;

	line = NULL;
	tokens = NULL;
	while (2 + 2 == 4)
	{
		free(line);
		signal_handler();
		line = user_input(data);
		if (!line)
			exit(0);
		if (!*line)
			continue ;
		get_tokens(&tokens, line, data);
		if (valid_syntax(tokens, data))
		{
			g_sig = 2;
			signal_handler();
			prepare_to_execute(data, tokens);
			g_sig = 0;
		}
		free_token_list(&tokens);
	}
	free(line);
}

void	free_data(t_all *data)
{
	free(data->home);
}

int	main(int argc, char **argv, char **env)
{
	t_all	data;

	g_sig = 0;
	(void)argc;
	init_data(&data, argv, env);
	minishell_loop(&data);
	free_data(&data);
	return (0);
}
